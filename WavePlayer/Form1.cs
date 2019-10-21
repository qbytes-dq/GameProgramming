using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

using Microsoft.DirectX;
using Microsoft.DirectX.AudioVideoPlayback;

using Microsoft.DirectX.DirectSound;
using System.Runtime.InteropServices;

namespace WindowsApplication1
{
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class Form1 : System.Windows.Forms.Form
    {
        #region stuff
        private Audio ourAudio = null;

        private Microsoft.DirectX.DirectSound.SecondaryBuffer ApplicationBuffer = null;
        private Microsoft.DirectX.DirectSound.Device ApplicationDevice = null;

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TrackBar trackBar3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar trackBar2;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Label label5;
        private System.ComponentModel.IContainer components;
        #endregion stuff

        public Form1()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
            Test text = new Test();
            text.startMain();


        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            Music_Cleanup();

            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.button5 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.trackBar3 = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.trackBar2 = new System.Windows.Forms.TrackBar();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.button6 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(0, 368);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(48, 48);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(8, 72);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(48, 48);
            this.button2.TabIndex = 1;
            this.button2.Text = "button2";
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(112, 368);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(48, 48);
            this.button3.TabIndex = 2;
            this.button3.Text = "button3";
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(160, 368);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(48, 48);
            this.button4.TabIndex = 3;
            this.button4.Text = "button4";
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.LargeChange = 1000;
            this.trackBar1.Location = new System.Drawing.Point(8, 16);
            this.trackBar1.Maximum = 88000;
            this.trackBar1.Minimum = 100;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(280, 45);
            this.trackBar1.SmallChange = 100;
            this.trackBar1.TabIndex = 4;
            this.trackBar1.TickFrequency = 4000;
            this.trackBar1.Value = 44000;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(80, 72);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "label1";
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(8, 120);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(56, 32);
            this.button5.TabIndex = 6;
            this.button5.Text = "button5";
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(80, 96);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(200, 16);
            this.label2.TabIndex = 7;
            this.label2.Text = "label2";
            // 
            // timer1
            // 
            this.timer1.Interval = 16;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // trackBar3
            // 
            this.trackBar3.LargeChange = 100;
            this.trackBar3.Location = new System.Drawing.Point(80, 208);
            this.trackBar3.Maximum = 500000;
            this.trackBar3.Name = "trackBar3";
            this.trackBar3.Size = new System.Drawing.Size(272, 45);
            this.trackBar3.SmallChange = 10;
            this.trackBar3.TabIndex = 8;
            this.trackBar3.TickFrequency = 100000;
            this.trackBar3.Value = 50000;
            this.trackBar3.Scroll += new System.EventHandler(this.trackBar3_Scroll);
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(80, 264);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(80, 16);
            this.label4.TabIndex = 9;
            this.label4.Text = "label4";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(80, 176);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 16);
            this.label3.TabIndex = 11;
            this.label3.Text = "label3";
            // 
            // trackBar2
            // 
            this.trackBar2.LargeChange = 100;
            this.trackBar2.Location = new System.Drawing.Point(80, 120);
            this.trackBar2.Maximum = 500000;
            this.trackBar2.Name = "trackBar2";
            this.trackBar2.Size = new System.Drawing.Size(272, 45);
            this.trackBar2.SmallChange = 10;
            this.trackBar2.TabIndex = 12;
            this.trackBar2.TickFrequency = 100000;
            this.trackBar2.Value = 50000;
            this.trackBar2.Scroll += new System.EventHandler(this.trackBar2_Scroll_1);
            // 
            // checkBox1
            // 
            this.checkBox1.Location = new System.Drawing.Point(176, 176);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(128, 16);
            this.checkBox1.TabIndex = 13;
            this.checkBox1.Text = "checkBox1";
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(112, 328);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(48, 40);
            this.button6.TabIndex = 14;
            this.button6.Text = "button6";
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(160, 328);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(144, 24);
            this.label5.TabIndex = 15;
            this.label5.Text = "label5";
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(360, 422);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.trackBar2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.trackBar3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).EndInit();
            this.ResumeLayout(false);

        }
        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new Form1());
        }
        //http://www.cc.jyu.fi/~ishorppu/projects/C-sharp_playing_music_and_audio_via_DX9.html

        // sound record
        //http://tek-tips.com/faqs.cfm?fid=4782


        #region button 1
        private void button1_Click(object sender, System.EventArgs e)
        {
            Music_Load(@"Z:\My Documents\My Music - parts\idj 126\breathless (1).MP3");
            Music_Play();
        }
        private int Music_Load(string filename)
        // load music file
        {
            try
            {
                ourAudio = new Audio(filename);
                ourAudio.Ending += new System.EventHandler(this.Music_ClipEnded);
            }
            catch
            {
                MessageBox.Show("Error", "Invalid/corrupted file?.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return -1;
            }
            return 0;
        }


        private int Music_Play()
        // play audio
        {
            try
            {
                ourAudio.Play();
                return 0;
            }
            catch
            {
                MessageBox.Show("Error", "Music_Play() failed.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return -1;
            }
        }


        private void Music_ClipEnded(object sender, System.EventArgs e)
        // repeat play!
        {
            if (ourAudio != null)
            {
                ourAudio.Stop();
                ourAudio.Play();
            }
        }


        private void Music_Cleanup()
        // clean up audio stuff
        {
            if (ourAudio != null)
                ourAudio.Dispose();
        }


        #endregion button 1

        #region Button2
        private void button2_Click(object sender, System.EventArgs e)
        {
            ApplicationDevice = new Microsoft.DirectX.DirectSound.Device();
            ApplicationDevice.SetCooperativeLevel(this, Microsoft.DirectX.DirectSound.CooperativeLevel.Priority);
            //SoundFX_LoadSoundFile(@"Z:\My Documents\My Music - parts\idj 126\breathless (1).MP3");
            //SoundFX_LoadSoundFile(@"Z:\mp3\hummingbird_0.01.02[1]\--autopilot--\hummingbird\root\wavfiles\cold fusion mafia - exteroceptor (edit).wav");
            SoundFX_LoadSoundFile(@"Z:\My Documents\My Programming\Pong\qbytespong.wav");
            SoundFX_PlaySound(true); // play sample (looping enabled)		
            timer1.Enabled = true;
            //trackBar2.Value = ApplicationBuffer
        }
        private bool SoundFX_LoadSoundFile(string name)
        // try to load sound file
        {
            try
            {
                ApplicationBuffer = new Microsoft.DirectX.DirectSound.SecondaryBuffer(name, ApplicationDevice);
                trackBar1.Value = ApplicationBuffer.Frequency;
                label1.Text = trackBar1.Value.ToString();
            }
            catch (Microsoft.DirectX.DirectSound.SoundException)
            {
                MessageBox.Show("Error", "SoundFX_LoadSoundFile() failed, file is missing/corrupted?.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return false;
            }
            return true;
        }
        private void SoundFX_PlaySound(bool bLooping)
        // plays sound file
        {
            if (null != ApplicationBuffer)
            {
                ApplicationBuffer.Frequency = trackBar1.Value;
                ApplicationBuffer.Play(0, (bLooping ?
                    Microsoft.DirectX.DirectSound.BufferPlayFlags.Looping :
                    Microsoft.DirectX.DirectSound.BufferPlayFlags.Default));
            }

            //ApplicationBuffer.
        }
        private void trackBar1_Scroll(object sender, System.EventArgs e)
        {
            if (ApplicationBuffer != null)
                ApplicationBuffer.Frequency = trackBar1.Value;

            if (bufferx != null)
            {
                BufferCaps cap;
                cap = bufferx.Caps;
                //bufferx.Pan = 10000;
                //cap.ControlFrequency = true;
                //int xxx = cap.BufferBytes / sps;
                int xxx1 = cap.PlayCpuOverhead;
                //label5.Text = xxx.ToString() + " " + xxx1.ToString();


                bufferx.Frequency = trackBar1.Value;
                Microsoft.DirectX.DirectSound.WaveFormat wfm = buffer_desc.Format;
                int bps = wfm.BitsPerSample;
                sps = wfm.AverageBytesPerSecond;
                //Play Buffer.
                //bufferx.Play(0,BufferPlayFlags.Default);
                //bufferx = buffer;
                //wfm.AverageBytesPerSecond = trackBar1.Value;

                //bufferx.Frequency =trackBar1.Value;
            }

            //if (trackBar1.Value != Convert.ToInt16(label1.Text))
            label1.Text = trackBar1.Value.ToString();
        }

        private void button5_Click(object sender, System.EventArgs e)
        {
            if (ApplicationBuffer != null)
                ApplicationBuffer.SetCurrentPosition(500000);
        }

        const int milla = 60 * 60;
        const int second = 60 * 60 * 60;
        const int minute = 60 * 60 * 60 * 60;

        int pmilla = 0;
        int psec = 0;
        int pmin = 0;

        private string pos(int cPos)
        {
            pmin = cPos / minute;
            cPos -= pmin * minute;

            psec = cPos / second;
            cPos -= psec * second;

            pmilla = cPos / milla;

            cPos /= 100;

            //psec = 
            //return pmin.ToString("d2") +":"+psec.ToString("d2")+":"+pmilla.ToString("d2");
            return pmin.ToString("d2") + ":" + psec.ToString("d2") + ":" + cPos.ToString("D4");
        }

        private void timer1_Tick(object sender, System.EventArgs e)
        {
            if (ApplicationBuffer != null)
            {
                int cPos, cWrit;
                ApplicationBuffer.GetCurrentPosition(out cPos, out cWrit);
                //ApplicationBuffer.;

                if (cPos > (trackBar3.Value * 100))
                {
                    ApplicationBuffer.SetCurrentPosition(trackBar2.Value * 100);
                    //ApplicationBuffer.Frequency = - 44000;
                }



                label2.Text = pos(cPos);
            }
            else
            {
                label2.Text = "waiting....";
            }

            if (devx != null)
            {
                int cPos, cWrit;
                bufferx.GetCurrentPosition(out cPos, out cWrit);

                cPos = cPos * 10;
                label2.Text = pos(cPos);


                BufferCaps cap;
                cap = bufferx.Caps;
                //int xxx = cap.BufferBytes / sps;
                int xxx = cap.BufferBytes / (trackBar1.Value * 2);
                int xxx1 = cap.PlayCpuOverhead;
                label5.Text = xxx.ToString() + " " + xxx1.ToString();
                xxx++;
            }


            //captureBuffer.GetCurrentPosition(out capturePos, out readPos); 
            //http://www.acoustics.salford.ac.uk/acoustics_world/id/VR/VirtualEnvironments.asp
        }
        private void trackBar2_Scroll_1(object sender, System.EventArgs e)
        {
            int cPos = trackBar2.Value * 100;
            //label3.Text = pmin.ToString() +":"+psec.ToString()+":"+pmilla.ToString();
            label3.Text = pos(cPos);
            if (checkBox1.Checked)
            {
                if (trackBar2.Value + 100 < trackBar3.Maximum)
                    trackBar3.Value = trackBar2.Value + 100;
                else
                    trackBar3.Value = trackBar3.Maximum;

                if (ApplicationBuffer != null)
                    ApplicationBuffer.SetCurrentPosition(trackBar2.Value * 100);
                trackBar3_Scroll(sender, e);
            }

        }
        private void trackBar3_Scroll(object sender, System.EventArgs e)
        {
            int cPos = trackBar3.Value * 100;
            //label4.Text = pmin.ToString() +":"+psec.ToString()+":"+pmilla.ToString();
            label4.Text = pos(cPos);

        }
        #endregion Button2

        BufferDescription buffer_desc;
        private void button3_Click(object sender, System.EventArgs e)
        {
            //Create and setup the sound device.
            Device dev = new Device();
            devx = dev;

            dev.SetCooperativeLevel(this, CooperativeLevel.Normal);

            //Create and setup the buffer description.
            buffer_desc = new BufferDescription();
            buffer_desc.ControlEffects = true; //this has to be true to use effects.
            buffer_desc.GlobalFocus = true; //play sound even if application loses focus.
            buffer_desc.ControlFrequency = true;

            //Create and setup the buffer for playing the sound.
            SecondaryBuffer buffer = new SecondaryBuffer(
                //@"C:\WINDOWS\Media\ding.wav", 
                @"Z:\My Documents\My Programming\Pong\qbytespong.wav",
                buffer_desc,
                dev);

            timer1.Enabled = true;
            //Create an array of effects descriptions, 
            //set the effect objects to echo and chorus and 
            //set it in the buffer.
            EffectDescription[] effects = new EffectDescription[3];
            //effects[0].GuidEffectClass = DSoundHelper.StandardEchoGuid;
            effects[1].GuidEffectClass = DSoundHelper.StandardChorusGuid;
            effects[0].GuidEffectClass = DSoundHelper.StandardFlangerGuid;
            effects[2].GuidEffectClass = DSoundHelper.StandardParamEqGuid;

            buffer.SetEffects(effects);

            //public class EchoEffect : System.MarshalByRefObject
            //    Member of Microsoft.DirectX.DirectSound

            //System.IntPtr lp=Application.lp;
            //EchoEffect efx = new EchoEffect(lp,buffer);
            //efx.
            Microsoft.DirectX.DirectSound.WaveFormat wfm = buffer_desc.Format;
            int bps = wfm.BitsPerSample;
            sps = wfm.AverageBytesPerSecond;
            msps = wfm.SamplesPerSecond;
            //Play Buffer.
            buffer.Play(0, BufferPlayFlags.Default);
            bufferx = buffer;

            trackBar1.Value = msps;
            label1.Text = trackBar1.Value.ToString();

        }
        int sps;
        int msps;
        /*in BufferCaps
        public int PlayCpuOverhead [  get]
            Member of Microsoft.DirectX.DirectSound.BufferCaps

        Summary:
        The processing overhead as a percentage of main processor cycles needed to mix this sound buffer. For hardware buffers, this member will be zero because the mixing is performed by the sound device. For software buffers, this member depends on the buffer format and the speed of the system processor.
         */
        private void button4_Click(object sender, System.EventArgs e)
        {
            //Create and setup the sound device.
            Device dev = new Device();
            dev.SetCooperativeLevel(this, CooperativeLevel.Normal);

            //Create and setup the buffer description.
            BufferDescription buffer_desc = new BufferDescription();
            buffer_desc.ControlEffects = true;	//this has to be true to use effects.
            buffer_desc.GlobalFocus = true;		//play sound even if application loses focus.

            //Create and setup the buffer for playing the sound.
            SecondaryBuffer buffer = new SecondaryBuffer(
                @"C:\WINDOWS\Media\ding.wav",
                buffer_desc,
                dev);

            //Create an array of effects descriptions, 
            //set the effect objects to echo and chorus and 
            //set it in the buffer.
            EffectDescription[] effects = new EffectDescription[2];
            effects[0].GuidEffectClass = DSoundHelper.StandardEchoGuid;
            effects[1].GuidEffectClass = DSoundHelper.StandardChorusGuid;
            buffer.SetEffects(effects);

            //Play Buffer.
            buffer.Play(0, BufferPlayFlags.Default);

        }

        Device devx;
        SecondaryBuffer bufferx;

        private void button6_Click(object sender, System.EventArgs e)
        {
            //Create and setup the sound device.
            //			Device dev = new Device();
            //			dev.SetCooperativeLevel(this,CooperativeLevel.Normal);

            //Create and setup the buffer description.
            BufferDescription buffer_desc = new BufferDescription();
            buffer_desc.ControlEffects = false;	//this has to be true to use effects.
            buffer_desc.GlobalFocus = true;		//play sound even if application loses focus.

            //Create and setup the buffer for playing the sound.
            //			SecondaryBuffer buffer = new SecondaryBuffer(
            //				@"C:\WINDOWS\Media\ding.wav", 
            //				buffer_desc, 
            //				dev);

            //Create an array of effects descriptions, 
            //set the effect objects to echo and chorus and 
            //set it in the buffer.
            EffectDescription[] effects = new EffectDescription[0];
            //			effects[0].GuidEffectClass = DSoundHelper.StandardEchoGuid;
            //			effects[1].GuidEffectClass = DSoundHelper.StandardChorusGuid;
            bufferx.SetEffects(effects);
            //bufferx.

            //Play Buffer.
            //			buffer.Play(0,BufferPlayFlags.Default);


        }






        /*
                The resources :
                The sound effects are freeware from http://www.flashkit.com/soundfx/
                The songs are for you to copy to folder Audio/Mp3/
                The Textures are from http://www.redfieldplugins.com/Textures.htm
                The DirectX objects are made with Maya 4.0
                The backgrounds are freeware from http://www.mediabuilder.com/  

        */
    }
}
