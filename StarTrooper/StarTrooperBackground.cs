#region Using directives

using System;
using System.Collections.Generic;
using System.Drawing;

#endregion

namespace StarTrooper
{
    public class Background: Sprite
    {
        public Background()
        {

        }

        protected Background(Background background): base(background)
        {

        }

        public override Object Clone()
        {
            return new Background(this);
        }

        public override void Update()
        {
            PointF position = Position;
            position.Y++;
            if (position.Y == 480 + 240)
                position.Y = -240;
            Position = position;
        }
    }
}
