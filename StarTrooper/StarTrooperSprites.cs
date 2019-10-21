#region Using directives

using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX.DirectInput;
using Microsoft.DirectX;

#endregion

using System.Windows.Forms;

namespace StarTrooper
{
  public class Trooper: Sprite
  {
    public override void Update()
    {
      //Type the code here to add the Trooper movement.
      #region TrooperMovement_code
      int vx = 0, vy = 0;
      if (Position.Y > 50 && Keyboard.IsPressed(Key.UpArrow))
        vy = -2;
      if (Position.Y < 450 && Keyboard.IsPressed(Key.DownArrow))
        vy = 2;
      if (Position.X > 30 && Keyboard.IsPressed(Key.LeftArrow))
      {
        vx = -2;
        ScaleX = -1;
      }
      if (Position.X < 610 && Keyboard.IsPressed(Key.RightArrow))
      {
        vx = 2;
        ScaleX = 1;
      }

      Velocity = new Vector2(vx, vy);

      if (Keyboard.IsTriggered(Key.Space))
      {
        Fire fire = (Fire)StarTrooper.Fire.Clone();
        fire.Position = new PointF(Position.X, Position.Y - 35);
        fire.Velocity = new Vector2(0, -4);
        Game.Add(fire);

        StarTrooper.Shoot.Play();
        m_Shots++;
        StarTrooper.Shots.Text = "Shots:" + m_Shots.ToString();
      }
      #endregion
    }
    static int m_Shots;
  }

  public class Condor : Sprite
  {
    public Condor()
    {
    }

    protected Condor(Condor condor): base(condor)
    {
    }

    public override Object Clone()
    {
      return new Condor(this);
    }

    public override void Update()
    {
      if (m_CollisionWithTrooper)
      {
        CollisionWithTrooper();
        return;
      }

      //Type the code here to add the Condor movement.
      #region CondorMovement_code
      Trooper b = StarTrooper.Trooper;

      if (AnimationIndex != 1)
      {
        Vector2 v = new Vector2(b.Position.X - Position.X, b.Position.Y - Position.Y);
        v.Normalize();

        Velocity = v;

        if (v.X >= 0)
          ScaleX = 1;
        else
          ScaleX = -1;

        List<Sprite> collidedSprites = Game.GetCollidedSprites(this);
        if (collidedSprites != null)
        {
          foreach (Sprite s in collidedSprites)
          {
            if (s is Fire)
            {
              StarTrooper.Die.Play();
              AnimationIndex = 1;
              m_Score++;
              StarTrooper.Score.Text = "Score: " + m_Score.ToString();
              Game.Remove(s);
              break;
            }
            else if (s is Trooper)
            {
              m_CollisionWithTrooper = true;
              StarTrooper.Die.Play();
              Animation.Stop();
              m_Score--;
              StarTrooper.Score.Text = "Score: " + m_Score.ToString();
              break;
            }
          }
        }
      }
      else
      {
        if (Animation.PlayingLastFrame)
          Game.Remove(this);
      }
      #endregion
    }

    private void CollisionWithTrooper()
    {
      Opacity -= 1;
      if (ScaleX < 0)
      {
        ScaleX += 0.01f;
        Rotation -= 0.03f;
      }
      else
      {
        ScaleX -= 0.01f;
        Rotation += 0.03f;
      }
      ScaleY -= 0.01f;
      if (Opacity <= 0)
        Game.Remove(this);
    }

    bool m_CollisionWithTrooper = false;
    static int m_Score;
  }

  public class Fire : Sprite
  {
    public Fire()
    {
    }

    protected Fire(Fire fire): base(fire)
    {
    }

    public override Object Clone()
    {
      return new Fire(this);
    }

    public override void Update()
    {
      float y = Position.Y;

      //Type the code here remove the Fire sprite
      #region FireSprite_code
      if (y < -100)
        Game.Remove(this);
      #endregion
      ScaleX = ScaleY = 1 + Math.Abs(0.001f *(480 - Position.Y));
    }
  }
}
