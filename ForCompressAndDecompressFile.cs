using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.IO;

namespace ForCompressAndDecompressFile
{
    class Program
    {
        static void Main(string[] args)
        {
            //for encode, and decode output path
            string file = @"C:\Users\dave.gan\Desktop\Test.exe";
            //for decode,  include .cs file is needed
            byte?[] buffer_encoded_input = null;// BF.BINARY_FILES.Test_exe; //
            //true for encode, false for decode
            bool isEncode = true; // true false    true for Encode,  false for Decode



            if (!file.Contains("."))
                throw new Exception("No extension file name in file name");
            if (isEncode)
            {
                byte[] buffer_input = System.IO.File.ReadAllBytes(file);
                byte?[] buffer_encoded_output = new byte?[buffer_input.Length + 1];
                //----------------------------------------------------
                BWTImplementation bwt = new BWTImplementation();
                bwt.BWT_Encode(buffer_input, buffer_encoded_output);
                //----------------------------------------------------
                RLC_Encode(ref buffer_encoded_output);
                //----------------------------------------------------
                ByteArray_To_TextFile(file, buffer_encoded_output);
                //----------------------------------------------------
                byte?[] CHECK1 = buffer_encoded_output.ToArray();
                byte[] CHECK2 = buffer_input.ToArray();
                RLC_Decode(ref CHECK1);
                bwt.BWT_Decode(CHECK1, CHECK2);
                if (buffer_input.SequenceEqual(CHECK2))
                {
                    throw (new Exception("TEST DECODE OK"));
                }
                else
                {
                    throw (new Exception("TEST DECODE FAIL"));
                }
                //----------------------------------------------------
            }
            else
            {
                //----------------------------------------------------
                RLC_Decode(ref buffer_encoded_input);
                //----------------------------------------------------
                byte[] buffer_decoded = new byte[buffer_encoded_input.Length - 1];
                BWTImplementation bwt = new BWTImplementation();
                bwt.BWT_Decode(buffer_encoded_input, buffer_decoded);
                //----------------------------------------------------
                ByteArray_To_BinaryFile(file.Substring(0, file.LastIndexOf(".")) + ".decode" + file.Substring(file.LastIndexOf("."), file.Length - file.LastIndexOf(".")), buffer_decoded);
                //----------------------------------------------------
            }
        }


        enum RLCState
        {
            E_INIT,
            E_CHECK_NEW_BYTE,
            E_SAME_BYTE_ALREADY,
        }

        static void RLC_Encode(ref byte?[] data)
        {
            List<byte?> b = new List<byte?>();
            int count = 0;
            int j = 0;
            RLCState state = RLCState.E_INIT;
            for (int i = 0; i < data.Length; i++)
            {
                if (count == 255)
                {
                    b.Add(b.Last());
                    b[b.Count - 1 - 1] = (byte)count;
                    b.Add(255);
                    b.Add(data[i]);
                    count = 1;
                    state = RLCState.E_CHECK_NEW_BYTE;
                    //-------------
                    continue;
                }

                if (i == data.Length - 1)
                {
                    if (state == RLCState.E_CHECK_NEW_BYTE)
                    {
                        if (b.Last() == 255)
                        {
                            b.Add(b.Last());
                            b[b.Count - 1 - 1] = (byte)count;
                        }
                        else
                        {
                            b.RemoveAt(b.Count - 1 - 1);
                        }
                        b.Add(data[i]);
                        continue;
                    }
                    else if (state == RLCState.E_SAME_BYTE_ALREADY)
                    {
                        b.Add(b.Last());
                        b.RemoveAt(b.Count - 1 - 1);
                        b.Add((byte)count);
                        b.Add(data[i]);
                        continue;
                    }
                }

                switch (state)
                {
                    case RLCState.E_INIT:
                        b.Add(255);
                        b.Add(data[i]);
                        count = 1;
                        state = RLCState.E_CHECK_NEW_BYTE;
                        break;


                    case RLCState.E_CHECK_NEW_BYTE:
                        if (b.Last() == data[i])
                        {
                            count++;
                            state = RLCState.E_SAME_BYTE_ALREADY;
                        }
                        else if (b.Last() == 255)
                        {
                            b.Add(b.Last());
                            b[b.Count - 1 - 1] = (byte)count;
                            b.Add(255);
                            b.Add(data[i]);
                            count = 1;
                        }
                        else
                        {
                            b.RemoveAt(b.Count - 1 - 1);
                            b.Add(255);
                            b.Add(data[i]);
                            count = 1;
                        }

                        break;

                    case RLCState.E_SAME_BYTE_ALREADY:
                        if (b.Last() == data[i])
                        {
                            count++;
                        }
                        else
                        {
                            b.Add(b.Last());
                            b[b.Count - 1 - 1] = (byte)count;
                            b.Add(255);
                            b.Add(data[i]);
                            count = 1;
                            state = RLCState.E_CHECK_NEW_BYTE;
                        }
                        break;

                    default:
                        break;
                }
            }
            data = b.ToArray();
        }

        static void RLC_Decode(ref byte?[] data)
        {
            List<byte?> b = new List<byte?>();

            int j = 0;
            int round = 0;
            for (int i = 0; i < data.Length; i++)
            {
                if (data[i] == 255 && j == 0)
                {
                    j = 1;
                }
                else if (j == 1)
                {
                    round = (int)data[i];
                    j = 2;
                }
                else if (j == 2)
                {
                    for (int k = 0; k < round; k++)
                        b.Add(data[i]);
                    j = 0;
                }
                else
                {
                    b.Add(data[i]);
                    j = 0;
                }
            }
            data = b.ToArray();
        }

        static public void ByteArray_To_TextFile(string fileName, byte[] byArray)
        {
            byte?[] byArray_ = new byte?[byArray.Length];
            for (int i = 0; i < byArray.Length; i++)
                byArray_[i] = byArray[i];
            ByteArray_To_TextFile(fileName, byArray_);
        }

        static public void ByteArray_To_TextFile(string inputFilePath, byte?[] byArray)
        {
            int lastindex = inputFilePath.LastIndexOf('\\');
            string fileName = inputFilePath.Substring(lastindex + 1, inputFilePath.Length - lastindex - 1);
            string outputFilePath = Path.GetFullPath(System.IO.Path.Combine(Environment.CurrentDirectory.ToString(), @"..\..") + @"\") + fileName;
            System.IO.TextWriter writeFile = new System.IO.StreamWriter(
               outputFilePath + ".cs");
            writeFile.Write(@"namespace BF");
            writeFile.WriteLine("");
            writeFile.Write(@"    {");
            writeFile.WriteLine("");
            writeFile.Write(@"static public partial class BINARY_FILES");
            writeFile.WriteLine("");
            writeFile.Write(@"    {");
            writeFile.WriteLine("");
            writeFile.Write(@"        static public byte?[] ");
            writeFile.Write(fileName.Replace(".", "_"));
            writeFile.Write(@" = new byte?[]");
            writeFile.WriteLine("");
            writeFile.Write(@"        {");
            writeFile.WriteLine("");
            writeFile.Write(@"            ");
            foreach (byte? b in byArray)
                if (b != null)
                    writeFile.Write(b + ",");
                else
                    writeFile.Write("null" + ",");
            writeFile.Write(@"");
            writeFile.WriteLine("");
            writeFile.Write(@"        };");
            writeFile.WriteLine("");
            writeFile.Write(@"    }");
            writeFile.WriteLine("");
            writeFile.Write(@"}");
            writeFile.Flush();
            writeFile.Close();
            writeFile = null;
        }

        static public void ByteArray_To_BinaryFile(string fileName, byte[] btArray)
        {
            using (var fs = new FileStream(fileName, FileMode.Create, FileAccess.Write))
            {
                fs.Write(btArray, 0, btArray.Length);
            }
        }
    }

    class BWTImplementation
    {
        public void BWT_Encode(byte[] buf_in_, byte?[] buffer_decoded)
        {
            //----------------------------------------------------
            int nLen = buffer_decoded.Length;
            byte?[] buf_in = new byte?[buf_in_.Length + 1];
            buf_in[buf_in_.Length] = null;
            for (int i = 0; i < buf_in_.Length; i++)
                buf_in[i] = buf_in_[i];
            //----------------------------------------------------
            int[] indices = new int[nLen];
            for (int i = 0; i < nLen; i++)
                indices[i] = i;
            //----------------------------------------------------
            Array.Sort(indices, 0, nLen, new BWTComparator(buf_in, nLen));
            //----------------------------------------------------
            for (int i = 0; i < nLen; i++)
            {
                int temp = (indices[i] + nLen - 1) % nLen;
                buffer_decoded[i] = (byte?)buf_in[temp];
            }
            //----------------------------------------------------
        }

        public void BWT_Decode(byte?[] buf_encoded, byte[] buf_decoded)
        {
            //----------------------------------------------------
            int nLen = buf_encoded.Length;
            int[] F = new int[nLen];
            int[] buckets = new int[0x100 + 1];
            int[] indices = new int[nLen];
            //----------------------------------------------------
            for (int i = 0; i < 0x100 + 1; i++)
                buckets[i] = 0;
            for (int i = 0; i < nLen; i++)
            {
                if (buf_encoded[i] != null)
                    buckets[(int)buf_encoded[i] + 1]++;
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
                if (buf_encoded[i] != null)
                    indices[buckets[(int)buf_encoded[i] + 1]++] = i;
                else
                    indices[buckets[0]++] = i;
            }
            //----------------------------------------------------
            int primary_key = -1;
            for (int i = 0; i < nLen; i++)
                if (buf_encoded[i] == null)
                { primary_key = i; break; }
            //----------------------------------------------------
            byte?[] buffer_de_ = new byte?[nLen];
            for (int i = 0, j = primary_key; i < nLen; i++)
            {
                buffer_de_[i] = buf_encoded[j];
                j = indices[j];
            }
            //----------------------------------------------------
            int p = -1;
            for (int k = 0; k < nLen; k++)
            {
                if (buffer_de_[k] != null)
                {
                    p++;
                    buf_decoded[p] = (byte)buffer_de_[k];
                }
            }
            //----------------------------------------------------
        }
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
