﻿using System.Runtime.CompilerServices;

namespace GloryEngine
{
    public struct Quaternion
    {
        #region Fields

        public float x;
        public float y;
        public float z;
        public float w;

        #endregion

        #region Constructor

        public Quaternion(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public Quaternion(Quaternion other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }

        #endregion

        #region Methods

        public static Quaternion Euler(float x, float y, float z)
            => Quaternion_Euler(x, y, z);

        #endregion

        #region API Methods

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Quaternion Quaternion_Euler(float x, float y, float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Quaternion operator +(Quaternion a, Quaternion b);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Quaternion operator -(Quaternion a, Quaternion b);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Quaternion operator *(Quaternion a, Quaternion b);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Quaternion operator *(Quaternion a, float factor);

        public override string ToString()
        {
            return string.Format("{0},{1},{2},{3}", x, y, z, w);
        }

        #endregion
    }
}
