using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.IO;

namespace BF
{
    static public partial class BINARY_FILES
    {
        static public byte?[] EMPTY_ARRAY = new byte?[]
        {
            
        };
    }
}

namespace ForCompressAndDecompressFile
{
    class Program
    {
        static void Main(string[] args)
        {
            //############## SETTING ##############
            byte?[] encodedArray = BF.BINARY_FILES.EMPTY_ARRAY;//EMPTY_ARRAY: encode process   、  Others: decode process
            string sourceFile = @"C:\Users\dave.gan\Desktop\Unzip.exe";//encode process: input file & output path   、   decode process: output path
            //############## SETTING ##############

            byte?[] decodedArray = null;

            if (encodedArray.Length == 0)  //########## encode process #########
            {
                //----------------------------------------------------
                byte?[] sourceArray = File.ReadAllBytes(sourceFile).Cast<byte?>().ToArray();

                encodedArray = sourceArray.ToArray();

                BWT.Encode(ref encodedArray); //ref for array is necessary if size changed

                RLC.Encode(ref encodedArray);

                ByteArray_To_CSharpTextFile(encodedArray, sourceFile + ".encoded.cs");

                //----------------------------------------------------
                //----------------------------------------------------
                //----------------------------------------------------
                //----------------------------------------------------testing
                decodedArray = encodedArray.ToArray();
                RLC.Decode(ref decodedArray);
                BWT.Decode(ref decodedArray);
                if (sourceArray.SequenceEqual(decodedArray))
                    throw (new Exception("TEST DECODE OK"));
                else
                    throw (new Exception("TEST DECODE FAIL"));
                //----------------------------------------------------
            }
            else  //                           ########## decode process #########
            {
                //----------------------------------------------------
                decodedArray = encodedArray.ToArray();

                RLC.Decode(ref decodedArray);

                BWT.Decode(ref decodedArray);

                ByteArray_To_BinaryFile(decodedArray.Cast<byte>().ToArray(), sourceFile + "_");
                //----------------------------------------------------
            }
        }

        static public void ByteArray_To_CSharpTextFile(byte?[] byArray, string outputPath)
        {
            int nLast = outputPath.LastIndexOf('\\');
            string fileName = outputPath.Substring(nLast + 1, outputPath.Length - nLast - 1);
            TextWriter writeFile = new StreamWriter(outputPath);
            var type = typeof(BF.BINARY_FILES);


            writeFile.WriteLine("namespace " + type.Namespace + "{");

            writeFile.WriteLine("static public partial class " + type.Name + "{");

            writeFile.Write("static public byte?[] ");
            writeFile.Write(fileName.Replace(".", "_"));
            writeFile.WriteLine(" = new byte?[]{");

            foreach (byte? b in byArray)
            {
                if (b != null)
                    writeFile.WriteLine(b + ",");
                else
                    writeFile.WriteLine("null" + ",");
            }

            writeFile.WriteLine("};");

            writeFile.WriteLine("}");

            writeFile.WriteLine("}");


            writeFile.Flush();
            writeFile.Close();
            writeFile = null;
        }

        static public void ByteArray_To_BinaryFile(byte[] btArray, string outputPath)
        {
            using (var fs = new FileStream(outputPath, FileMode.Create, FileAccess.Write))
            {
                fs.Write(btArray, 0, btArray.Length);
            }
        }
    }

    class RLC
    {
        public static void Encode(ref byte?[] arr1)
        {
            byte?[] arr2 = new byte?[arr1.Length * 2]; //default value: null

            int ind = -1;
            byte same = 1;
            byte? target = arr1[0];

            for (int i = 1; i < arr1.Length; i++)
            {
                if (arr1[i - 1] == arr1[i] && same != 255)
                {
                    same++;
                }
                else
                {
                    if (same > 1 || target == 255)
                    {
                        arr2[++ind] = 255;
                        arr2[++ind] = same;
                        arr2[++ind] = target;
                    }
                    else
                    {
                        arr2[++ind] = target;
                    }
                    target = arr1[i];
                    same = 1;
                }
            }
            arr2[++ind] = 255;
            arr2[++ind] = same;
            arr2[++ind] = target;

            Array.Resize(ref arr2, ind + 1);
            arr1 = arr2.ToArray();
        }

        public static void Decode(ref byte?[] arr1)
        {
            List<byte?> arr2 = new List<byte?>();

            for (int i = 0; i < arr1.Length; i++)
            {
                if (arr1[i] == 255)
                {
                    byte? same = arr1[++i];
                    ++i;
                    for (byte j = 0; j < same; j++)
                        arr2.Add(arr1[i]);
                }
                else
                {
                    arr2.Add(arr1[i]);
                }
            }
            arr1 = arr2.ToArray();
        }
    }

    class BWT
    {
        static public void Encode(ref byte?[] arr1)
        {
            int outLen = arr1.Length + 1;//+1: for primarykey(null)

            byte?[] arr2 = arr1.ToArray();
            Array.Resize(ref arr2, outLen);

            arr1 = new byte?[outLen];
            //----------------------------------------------------
            int[] indices = new int[outLen];
            for (int i = 0; i < outLen; i++)
                indices[i] = i;
            //----------------------------------------------------
            Array.Sort(indices, 0, outLen, new BWTComparator(arr2, outLen));
            //----------------------------------------------------
            for (int i = 0; i < outLen; i++)
            {
                int temp = (indices[i] + outLen - 1) % outLen;
                arr1[i] = (byte?)arr2[temp];
            }
            //----------------------------------------------------
        }

        static public void Decode(ref byte?[] arr1)
        {
            byte?[] arr2 = arr1.ToArray();
            arr1 = new byte?[arr2.Length - 1];
            //----------------------------------------------------
            int nLen = arr2.Length;
            int[] F = new int[nLen];
            int[] buckets = new int[0x100 + 1];
            int[] indices = new int[nLen];
            //----------------------------------------------------
            for (int i = 0; i < 0x100 + 1; i++)
                buckets[i] = 0;
            for (int i = 0; i < nLen; i++)
            {
                if (arr2[i] != null)
                    buckets[(int)arr2[i] + 1]++;
                else
                    buckets[0]++;
            }
            //----------------------------------------------------
            for (int i = 0, k = 0; i < 0x100 + 1; i++)
            {
                for (int j = 0; j < buckets[i]; j++)
                {
                    F[k++] = i;
                }
            }
            //----------------------------------------------------
            for (int i = 0, j = 0; i < 0x100 + 1; i++)
            {
                while (i > F[j] && j < nLen - 1)
                {
                    j++;
                }
                buckets[i] = j;
            }
            //----------------------------------------------------
            for (int i = 0; i < nLen; i++)
            {
                if (arr2[i] != null)
                    indices[buckets[(int)arr2[i] + 1]++] = i;
                else
                    indices[buckets[0]++] = i;
            }
            //----------------------------------------------------
            int primary_key = -1;
            for (int i = 0; i < nLen; i++)
                if (arr2[i] == null)
                { primary_key = i; break; }
            //----------------------------------------------------
            byte?[] buffer_de_ = new byte?[nLen];
            for (int i = 0, j = primary_key; i < nLen; i++)
            {
                buffer_de_[i] = arr2[j];
                j = indices[j];
            }
            //----------------------------------------------------
            int p = -1;
            for (int k = 0; k < nLen; k++)
            {
                if (buffer_de_[k] != null)
                {
                    p++;
                    arr1[p] = (byte)buffer_de_[k];
                }
            }
            //----------------------------------------------------
        }

        class BWTComparator : IComparer<int>
        {
            private byte?[] rotlexcmp_buf = null;
            private int rottexcmp_bufsize = 0;

            public BWTComparator(byte?[] array, int size)
            {
                rotlexcmp_buf = array;
                rottexcmp_bufsize = size;
            }

            public int Compare(int li, int ri)
            {
                int ac = rottexcmp_bufsize;
                while (rotlexcmp_buf[li] == rotlexcmp_buf[ri])
                {
                    if (++li == rottexcmp_bufsize)
                        li = 0;
                    if (++ri == rottexcmp_bufsize)
                        ri = 0;
                    if (--ac <= 0)
                        return 0;
                }
                if (rotlexcmp_buf[li] > rotlexcmp_buf[ri] || rotlexcmp_buf[ri] == null)
                    return 1;

                return -1;
            }
        }
    }
}
