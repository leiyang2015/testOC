#ifndef __UINT128_H__
#define __UINT128_H__

#include <stdint.h>
#include <string>
//#include "bigint.hpp"

namespace bytetrade {
    /*
     typedef struct uint128 {
     uint64_t high, low;
     
     uint128() {
     high = 0;
     low = 0;
     }
     
     uint128(uint32_t v) {
     high = 0;
     low = v;
     }
     
     uint128(uint64_t v) {
     high = 0;
     low = v;
     }
     
     uint128::operator std::string ()const
     {
     if(*this == 0) { return "0"; }
     
     // at worst it will be size digits (base 2) so make our buffer
     // that plus room for null terminator
     static char sz [128 + 1];
     sz[sizeof(sz) - 1] = '\0';
     
     uint128 ii(*this);
     int i = 128 - 1;
     
     while (ii != 0 && i) {
     
     uint128 remainder;
     divide(ii, uint128(10), ii, remainder);
     sz [--i] = "0123456789abcdefghijklmnopqrstuvwxyz"[remainder.to_integer()];
     }
     
     return &sz[i];
     }
     
     } uint128_t;
     
     void uint128RShift(uint128_t *uint128var);
     void uint128Set(uint128_t *uint128var, uint64_t value);
     uint8_t uint128GetByte(uint128_t *uint128var, uint8_t num);
     void uint128Multiply(uint128_t *uint128var, uint64_t v1, uint64_t v2);
     uint64_t uint128Divide(uint128_t *uint128var, uint64_t divisor);*/
    
    class uint128
    {
        
        
        public:
        uint128():hi(0),lo(0){}
        uint128( uint32_t l ):hi(0),lo(l){}
        uint128( int32_t l ):hi( -(l<0) ),lo(l){}
        uint128( int64_t l ):hi( -(l<0) ),lo(l){}
        uint128( uint64_t l ):hi(0),lo(l){}
        uint128( const std::string& s );
        uint128( uint64_t _h, uint64_t _l )
        :hi(_h),lo(_l){}
        //    uint128( const bigint& bi );
        
        operator std::string()const;
        //      operator bigint()const;
        
        
        bool     operator == ( const uint128& o )const{ return hi == o.hi && lo == o.lo;             }
        bool     operator != ( const uint128& o )const{ return hi != o.hi || lo != o.lo;             }
        bool     operator < ( const uint128& o )const { return (hi == o.hi) ? lo < o.lo : hi < o.hi; }
        bool     operator < ( const int64_t& o )const { return *this < uint128(o); }
        bool     operator !()const                    { return !(hi !=0 || lo != 0);                 }
        uint128  operator -()const                    { return ++uint128( ~hi, ~lo );                }
        uint128  operator ~()const                    { return uint128( ~hi, ~lo );                  }
        
        uint128& operator++()    {  hi += (++lo == 0); return *this; }
        uint128& operator--()    {  hi -= (lo-- == 0); return *this; }
        uint128  operator++(int) { auto tmp = *this; ++(*this); return tmp; }
        uint128  operator--(int) { auto tmp = *this; --(*this); return tmp; }
        
        uint128& operator |= ( const uint128& u ) { hi |= u.hi; lo |= u.lo; return *this; }
        uint128& operator &= ( const uint128& u ) { hi &= u.hi; lo &= u.lo; return *this; }
        uint128& operator ^= ( const uint128& u ) { hi ^= u.hi; lo ^= u.lo; return *this; }
        uint128& operator <<= ( const uint128& u );
        uint128& operator >>= ( const uint128& u );
        
        uint128& operator += ( const uint128& u ) { const uint64_t old = lo; lo += u.lo;  hi += u.hi + (lo < old); return *this; }
        uint128& operator -= ( const uint128& u ) { return *this += -u; }
        uint128& operator *= ( const uint128& u );
        uint128& operator /= ( const uint128& u );
        uint128& operator %= ( const uint128& u );
        
        
        friend uint128 operator + ( const uint128& l, const uint128& r )   { return uint128(l)+=r;   }
        friend uint128 operator - ( const uint128& l, const uint128& r )   { return uint128(l)-=r;   }
        friend uint128 operator * ( const uint128& l, const uint128& r )   { return uint128(l)*=r;   }
        friend uint128 operator / ( const uint128& l, const uint128& r )   { return uint128(l)/=r;   }
        friend uint128 operator % ( const uint128& l, const uint128& r )   { return uint128(l)%=r;   }
        friend uint128 operator | ( const uint128& l, const uint128& r )   { return uint128(l)=(r);  }
        friend uint128 operator & ( const uint128& l, const uint128& r )   { return uint128(l)&=r;   }
        friend uint128 operator ^ ( const uint128& l, const uint128& r )   { return uint128(l)^=r;   }
        friend uint128 operator << ( const uint128& l, const uint128& r )  { return uint128(l)<<=r;  }
        friend uint128 operator >> ( const uint128& l, const uint128& r )  { return uint128(l)>>=r;  }
        friend bool    operator >  ( const uint128& l, const uint128& r )  { return r < l;           }
        friend bool    operator >  ( const uint128& l, const int64_t& r )  { return uint128(r) < l;           }
        friend bool    operator >  ( const int64_t& l, const uint128& r )  { return r < uint128(l);           }
        
        friend bool    operator >=  ( const uint128& l, const uint128& r ) { return l == r || l > r; }
        friend bool    operator >=  ( const uint128& l, const int64_t& r ) { return l >= uint128(r); }
        friend bool    operator >=  ( const int64_t& l, const uint128& r ) { return uint128(l) >= r; }
        friend bool    operator <=  ( const uint128& l, const uint128& r ) { return l == r || l < r; }
        friend bool    operator <=  ( const uint128& l, const int64_t& r ) { return l <= uint128(r); }
        friend bool    operator <=  ( const int64_t& l, const uint128& r ) { return uint128(l) <= r; }
        
        
        uint32_t to_integer()const
        {
            // assert( hi == 0 );
            uint32_t lo32 = (uint32_t) lo;
            // assert( lo == lo32 );
            return lo32;
        }
        uint64_t to_uint64()const
        {
            //assert( hi == 0 );
            return lo;
        }
        uint32_t low_32_bits()const { return (uint32_t) lo; }
        uint64_t low_bits()const  { return lo; }
        uint64_t high_bits()const { return hi; }
        
        
        
        static void full_product( const uint128& a, const uint128& b, uint128& result_hi, uint128& result_lo );
        
        uint8_t popcount() const;
        
        // fields must be public for serialization
        uint64_t hi;
        uint64_t lo;
    };
    
    typedef uint128 uint128_t;
    
}

#endif

