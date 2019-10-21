#region Using directives

using System;
using Microsoft.DirectX.DirectInput;

#endregion

namespace StarTrooper
{
    public sealed class Keyboard
    {
        struct KeyState
        {
            public bool IsPressed;
            public bool IsTriggered;
            public bool WasPressed;
        };

        static KeyState[] m_KeyStates = new KeyState[256];
        
        public static bool IsPressed(Key key)
        {
            return m_KeyStates[(int)key].IsPressed;
        }

        public static bool IsTriggered(Key key)
        {
            return m_KeyStates[(int)key].IsTriggered;
        }

        public static void Update()
        {
            for(int i = 0; i < 256; i++)
                m_KeyStates[i].IsPressed = false;

            foreach(Key key in Game.DIDevice.GetPressedKeys())
                m_KeyStates[(int)key].IsPressed = true;

            for (int i = 0; i < 256; i++)
            {
                if (m_KeyStates[i].IsPressed)
                {
                    if (m_KeyStates[i].WasPressed)
                        m_KeyStates[i].IsTriggered = false;
                    else
                    {
                        m_KeyStates[i].WasPressed = true;
                        m_KeyStates[i].IsTriggered = true;
                    }
                }
                else
                {
                    m_KeyStates[i].WasPressed = false;
                    m_KeyStates[i].IsTriggered = false;
                }
            }
        }

        private Keyboard()
        {

        }
    }
}
