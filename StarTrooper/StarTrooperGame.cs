#region Using directives

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;


#endregion

namespace StarTrooper // Hour 8
{
  public class StarTrooper: Game
  {
    public StarTrooper()
    {
      FrameRate = 60;
      Resolution = new Size(640, 480);

      PicturesPath = Application.StartupPath + "\\StarTrooperResources\\Pictures\\";
      MusicPath = Application.StartupPath + "\\StarTrooperResources\\Music\\";
      SoundPath = Application.StartupPath + "\\StarTrooperResources\\Sounds\\";
    }

    public override void InitializeResources()
    {
      #region Background
      //Type the code here to add the background to the game.
      #region Background_code
      Picture background = new Picture("Background.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(background);

      Frame backGroundFrame = new Frame(background, 0);
      Animation backGroundAnimation = new Animation();
      backGroundAnimation.Add(backGroundFrame);
      Background bg = new Background();
      bg.Add(backGroundAnimation);
      bg.Position = new Point(320, 240);
      bg.ScaleX = 640.0f / background.Width;
      bg.ScaleY = 480.0f / background.Height;
      bg.ZOrder = 10;
      Game.Add(bg);

      Background bg2 = (Background)bg.Clone();
      bg2.Position = new Point(320, -240);
      Add(bg2);
      #endregion
      #endregion

      #region Trooper
      //Type the code here to add the Trooper sprite.
      #region Trooper_code

      Picture trooper01 = new Picture("trooper01.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper01);
      Picture trooper02 = new Picture("trooper02.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper02);
      Picture trooper03 = new Picture("trooper03.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper03);
      Picture trooper04 = new Picture("trooper04.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper04);
      Picture trooper05 = new Picture("trooper05.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper05);
      Picture trooper06 = new Picture("trooper06.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(trooper06);

      Frame afTrooper01 = new Frame(trooper01, 5);
      Frame afTrooper02 = new Frame(trooper02, 5);
      Frame afTrooper03 = new Frame(trooper03, 5);
      Frame afTrooper04 = new Frame(trooper04, 5);
      Frame afTrooper05 = new Frame(trooper05, 5);
      Frame afTrooper06 = new Frame(trooper06, 5);

      Animation trooperAnimation = new Animation();
      trooperAnimation.Add(afTrooper01);
      trooperAnimation.Add(afTrooper02);
      trooperAnimation.Add(afTrooper03);
      trooperAnimation.Add(afTrooper04);
      trooperAnimation.Add(afTrooper05);
      trooperAnimation.Add(afTrooper06);
      trooperAnimation.Play();
      trooperAnimation.Loop = true;

      Trooper trooper = new Trooper();
      trooper.Add(trooperAnimation);
      trooper.Position = new Point(320, 450);
      Game.Add(trooper);
      Trooper = trooper;
      #endregion
      #endregion

      #region Condor
      //Type the code here to add the Condor sprite.
      #region Condor_code

      Picture condor01 = new Picture("condor01.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condor01);
      Picture condor02 = new Picture("condor02.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condor02);
      Picture condor03 = new Picture("condor03.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condor03);
      Picture condor04 = new Picture("condor04.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condor04);


      Frame afcondor01 = new Frame(condor01, 5);
      Frame afcondor02 = new Frame(condor02, 5);
      Frame afcondor03 = new Frame(condor03, 5);
      Frame afcondor04 = new Frame(condor04, 5);


      Animation condorAnimation = new Animation();
      condorAnimation.Add(afcondor01);
      condorAnimation.Add(afcondor02);
      condorAnimation.Add(afcondor03);
      condorAnimation.Add(afcondor04);
      condorAnimation.Play();
      condorAnimation.Loop = true;

      Picture condorExplosion01 = new Picture("condorExplosion01.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condorExplosion01);
      Picture condorExplosion02 = new Picture("condorExplosion02.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condorExplosion02);
      Picture condorExplosion03 = new Picture("condorExplosion03.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(condorExplosion03);

      Frame afcondorExplosion01 = new Frame(condorExplosion01, 4);
      Frame afcondorExplosion02 = new Frame(condorExplosion02, 3);
      Frame afcondorExplosion03 = new Frame(condorExplosion03, 4);


      Animation condorExplosion = new Animation();
      condorExplosion.Add(afcondorExplosion01);
      condorExplosion.Add(afcondorExplosion02);
      condorExplosion.Add(afcondorExplosion03);
      condorExplosion.Play();

      Condor condor = new Condor();
      condor.Add(condorAnimation);
      condor.Add(condorExplosion);
      Condor = condor;
      #endregion
      #endregion

      #region Fire
      //Type the code here to add the Fire sprite.
      #region Fire_code

      Picture fire01 = new Picture("fire01.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(fire01);
      Picture fire02 = new Picture("fire02.bmp", Color.FromArgb(0, 255, 0));
      Game.Add(fire02);

      Frame affire01 = new Frame(fire01, 5);
      Frame affire02 = new Frame(fire02, 5);

      Animation fireAnimation = new Animation();
      fireAnimation.Add(affire01);
      fireAnimation.Add(affire02);
      fireAnimation.Play();
      fireAnimation.Loop = true;

      Fire fire = new Fire();
      fire.ZOrder = -10;
      fire.Add(fireAnimation);
      Fire = fire;
      #endregion
      #endregion

      #region FontText
      //Type the code here to add the Text object.
      #region FontText_code
      Font font = new Font("Arial", 14.0f, FontStyle.Regular);
      Game.Add(font);

      Text2D FrameRate = new FrameRate(font);
      Game.Add(FrameRate);

      Text2D Shots = new Text2D(font);
      Shots.Text = "Shots: 0";
      Shots.Position = new Point(0, 0);
      Shots.Color = Color.Green;
      StarTrooper.Shots = Shots;
      Game.Add(Shots);

      Text2D Score = new Text2D(font);
      Score.Text = "Score: 0";
      Score.Position = new Point(150, 0);
      Score.Color = Color.Red;
      StarTrooper.Score = Score;
      Game.Add(Score);
      #endregion
      #endregion

      #region SoundMusic
      //Type the code here to add the Sound object.
      #region SoundMusic_code
      Shoot = new Sound("Shoot.wav");
      Game.Add(Shoot);

      Die = new Sound("Die.wav");
      Game.Add(Die);

      Music = new Music("music.wav");
      Game.Add(Music);
      Music.Play();
      #endregion
      #endregion
    }

    public override void Update()
    {
      m_GameLoops++;
      if (m_GameLoops % 200 == 0)
      {
        //Type the code here to add the Condor sprite positioning.
        #region Condor_code
        Condor condor = (Condor)Condor.Clone();
        condor.Position = new Point(m_Random.Next(-100, 740), -150);
        Game.Add(condor);
        #endregion
      }

      //Type the code here to add the background music.
      #region PlayMusic_code
      if (!Music.IsPlaying)
        Music.Play();
      #endregion
    }

    //Type the code here to add the objects prototype.
    #region Public_code
    public static Trooper Trooper;
    public static Condor Condor;
    public static Fire Fire;

    public static Sound Shoot;
    public static Sound Die;

    public static Text2D Shots;
    public static Text2D Score;
     
    public static Music Music;
    #endregion

    #region PrivateData

    Random m_Random = new Random();
    int m_GameLoops;

    #endregion
  }
}
