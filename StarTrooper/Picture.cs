#region Using directives

using System;
using System.Drawing;
using Microsoft.DirectX.Direct3D;

#endregion

namespace StarTrooper
{
    public class Picture: IDisposable
    {
        public Picture(string fileName, Color colorKey)
        {
            ImageInformation imageInformation = TextureLoader.ImageInformationFromFile(Game.PicturesPath + fileName);
            m_Width = imageInformation.Width;
            m_Height = imageInformation.Height;
            m_Texture = TextureLoader.FromFile(Game.Device, Game.PicturesPath + fileName, 0, 0, 1, Usage.None, Format.Unknown, Pool.Managed, Filter.None, Filter.None, colorKey.ToArgb());
        }

        public virtual void Dispose()
        {
            m_Texture.Dispose();
            m_Texture = null;
            m_Disposed = true;
        }

        public bool Disposed
        {
            get
            {
                return m_Disposed;
            }
        }

        public Texture Texture
        {
            get
            {
                return m_Texture;
            }
        }

        public int Width
        {
            get
            {
                return m_Width;
            }
        }

        public int Height 
        {
            get
            {
                return m_Height;
            }
        }

        #region PrivateData
        
        private Texture m_Texture;
        private int m_Width;
        private int m_Height;
        private bool m_Disposed = false;

        #endregion
    }
}
