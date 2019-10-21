using System;
using System.Globalization;

namespace SoundFX
{
	/// <summary>
	/// Summary description for FFT.
	/// </summary>
	public class FFT
	{
		public int cPos;
		public int cWrit;

		public int FFT_LEN			= 1024;
		public int FFT_Chnl			= 2;
		public int FFT_Frequency	= 44100;

		//public uint p_nSamples		= 1024;

		public short[] StreamCaptureData;

		double[] p_lpRealOut;	//	= new double[2048];
		double[] p_lpRealIn;	//	= new double[2048];
		double[] p_lpImagIn	;	//	= new double[2048];
		double[] p_lpImagOut;	//	= new double[2048];

		public double[] fdraw	= new double[2048];

		public void FFT_Plug_Hz(double slide,int Hz)
		{
			for (int test = 0; test < FFT_LEN; test++)
			{
				StreamCaptureData[test]  = (short)(1600 * Math.Sin ((slide * Math.PI) *    Hz * test / FFT_Frequency));
				// 10 kHz calibration wave
				//63, 125, 250, 500, 1k, 2k, 4k, 8k, 16k Hz 
				//StreamCaptureData[test]  = (short)(1600 * Math.Sin ((slide * Math.PI) *    63.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *   125.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *   250.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *   500.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *  1000.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *  2000.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI *  4000.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin ((slide * Math.PI) *  8000.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI * 11020.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI * 16000.0 * test / FFT_Frequency));
				//StreamCaptureData[test] += (short)(1600 * Math.Sin (2 * Math.PI * 20000.0 * test / FFT_Frequency));
			}
		}

		public FFT()
		{
			// Construct
			//
			// TODO: Add constructor logic here
			//
			p_lpRealOut	= new double[FFT_LEN * FFT_Chnl];
			p_lpRealIn	= new double[FFT_LEN * FFT_Chnl];
			p_lpImagIn	= new double[FFT_LEN * FFT_Chnl];
			p_lpImagOut	= new double[FFT_LEN * FFT_Chnl];
		}

		public string Pos2Time()
		{
			double hh = (cPos/(FFT_Frequency/10000))/(FFT_Chnl*2);
			double mm = (cPos/(FFT_Frequency/100))/(FFT_Chnl*2);
			double ss = (cPos/(FFT_Frequency/100))/(FFT_Chnl*2);
			double ms = (cPos/(FFT_Frequency/100))/(FFT_Chnl*2);

			return hh.ToString("n2");
		}

		/// <summary>
		/// reverse bits
		/// </summary>
		/// <param name="p_nX"></param>
		/// <returns></returns>
		private bool IsPowerOfTwo(uint p_nX)
		{
			if (p_nX < 2) return false;
			uint np_nX = p_nX &(p_nX-1);
			//if (p_nX &(p_nX-1);
			if (np_nX != 0)
				return false;
			return true;
		}

		/// <summary>
		/// return needed bits for fft
		/// </summary>
		/// <param name="p_nSamples"></param>
		/// <returns></returns>
		private uint NumberOfBitsNeeded (uint p_nSamples)
		{
			uint i;

			if (p_nSamples < 2)
				return 0;

			int it = 1;
			for (i = 0 ;; i++)	
			{
				uint t = i << 1;
				//if (p_nSamples & (1 << i))
				if (it == p_nSamples)// could be very bad loop
				{
					//i=11;  // works well
					i++;
					return i;
				}

				it*=2;
			}
		}

		/// <summary>
		/// check if a number is a power of 2
		/// </summary>
		/// <param name="p_nIndex"></param>
		/// <param name="p_nBits"></param>
		/// <returns></returns>
		private uint ReverseBits(uint p_nIndex, uint p_nBits)
		{
			uint i, rev;
			for (i = rev = 0;i < p_nBits; i++)
			{
				rev = (rev << 1) | (p_nIndex & 1);
				p_nIndex  >>= 1;				
			}
			return rev;
		}


		/// <summary>
		/// Get Frequency Intensity
		/// </summary>
		/// <param name="re"></param>
		/// <param name="im"></param>
		/// <returns></returns>
		public double GetFrequencyIntensity(double re, double im)
			   {
				   return Math.Sqrt((re*re)+(im*im));
			   }

		/// <summary>
		/// Get Frequency Intensity
		/// </summary>
		/// <param name="re"></param>
		/// <param name="im"></param>
		/// <returns></returns>


		public double GetFrequencyIntensity(int i)
		{
			//re = fout[i];
			//im = foutimg[i];
			//return Math.Sqrt((re*re)+(im*im));
			return Math.Sqrt((p_lpRealOut[i]*p_lpRealOut[i])+(p_lpImagOut[i]*p_lpImagOut[i]));
		}

		/// <summary>
		/// displayFreq
		/// </summary>
		/// <returns></returns>
		public void displayFreq()
		{
			double re,im;

			//double[] fdraw	= new double[FFT_LEN];

			for(int i=0;i<FFT_LEN/2;i++)
			{
//				re = fout[i];
//				im = foutimg[i];
				re = p_lpRealOut[(int)i];
				im = p_lpImagOut[(int)i];

				//get frequency intensity and scale to 0..256 range
				fdraw[i]=(GetFrequencyIntensity(re,im));
			}
			//return fdraw;
		}

		/// <summary>
		/// return a frequency from the base freq and num of samples
		/// </summary>
		/// <param name="p_nBaseFreq"></param>
		/// <param name="p_nSamples"></param>
		/// <param name="p_nIndex"></param>
		/// <returns></returns>
		public double IndexToFrequency(uint p_nBaseFreq, uint p_nSamples, uint p_nIndex)
		{
			if (p_nIndex >=p_nSamples)
				return 0.0;
			else
				if (p_nIndex <= p_nSamples/2)
					return ( (double)p_nIndex / (double)p_nSamples * p_nBaseFreq );
			else
				return ( -(double)(p_nSamples-p_nIndex) / (double)p_nSamples * p_nBaseFreq );
         }


		/// <summary>
		/// do the fft for double numbers
		/// </summary>
		/// <param name="p_nSamples"></param>
		/// <param name="p_bInverseTransform"></param>
		public void fft_double(uint p_nSamples, bool p_bInverseTransform, int slide )
		{
			for (int p = 0; p < this.FFT_LEN; p++)
			{
				p_lpRealIn[p] = (double)StreamCaptureData[p];
				int x = 0;
			}

			uint NumBits;
			uint i, j, k, n;
			uint BlockSize, BlockEnd;

			double angle_numberator = 2.0 * Math.PI;
			//double angle_numberator = 2.12 * Math.PI;
			double tr, ti;

			if (!IsPowerOfTwo(p_nSamples))
				//return p_lpRealOut;
				return;

			if (p_bInverseTransform) 
				angle_numberator = - angle_numberator;

			NumBits = NumberOfBitsNeeded(p_nSamples);

			for( i=0; i < p_nSamples; i++ )
			{		
				p_lpRealOut[i] = 0.0;
				p_lpImagOut[i] = 0.0;
				p_lpImagIn[i] = 0.0;
			}

			for (i = 0 ; i < p_nSamples; i++)
			{
				j = ReverseBits( i, NumBits);
				p_lpRealOut[j] = p_lpRealIn[i];
			}

			BlockEnd = 1;

			int cnt  = 0;

			for (BlockSize = 2; BlockSize <= p_nSamples; BlockSize <<= 1) //BlockSize << 1 
			{
				double delta_angle = angle_numberator / (double)BlockSize;
				double sm2 = Math.Sin (-2 * delta_angle);
				double sm1 = Math.Sin (-delta_angle);
				double cm2 = Math.Cos (-2 * delta_angle);
				double cm1 = Math.Cos (-delta_angle);
				double w = 2 * cm1;

				double[] ar	= new double[3];
				double[] ai	= new double[3];

				for ( i = 0 ; i < p_nSamples; i += BlockSize)
				{// add comment
					ar[2] = cm2;
					ar[1] = cm1;
					ai[2] = sm2;
					ai[1] = sm1;

					for (j = i, n = 0; n < BlockEnd; j++, n++)
					{
						ar[0] = w*ar[1] - ar[2];
						ar[2] = ar[1];
						ar[1] = ar[0];

						ai[0] = w*ai[1] - ai[2];
						ai[2] = ai[1];
						ai[1] = ai[0];

						k = j + BlockEnd;
						tr = ar[0]*p_lpRealOut[k] - ai[0]*p_lpImagOut[k];
						ti = ar[0]*p_lpImagOut[k] + ai[0]*p_lpRealOut[k];

						p_lpRealOut[k] = p_lpRealOut[j] - tr;
						p_lpImagOut[k] = p_lpImagOut[j] - ti;

						p_lpRealOut[j] += tr;
						p_lpImagOut[j] += ti;

						cnt++;
					}
				}
				BlockEnd = BlockSize;
			}

			if (p_bInverseTransform)
			{
				double denom = (double)p_nSamples;

				for (i = 0; i < p_nSamples; i++)
				{
					p_lpRealOut[i] /= denom;
					p_lpImagOut[i] /= denom;
				}
			}

//			return p_lpRealOut;
		}
	}
}
