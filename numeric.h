// Copyright (c) 2004
//
// CIYAM Pty. Ltd.
// ACN 093 704 539
//
// ALL RIGHTS RESERVED
//
// Permission to use this software for non-commercial purposes is hereby granted. Permission to
// distribute this software privately is granted provided that the source code is unaltered and
// complete or that any alterations and omissions have been first approved by CIYAM. Commercial
// usage of this software is not permitted without first obtaining a license for such a purpose
// from CIYAM. This software may not be publicly distributed unless written permission to do so
// has been obtained from CIYAM.

#ifndef NUMERIC_H
#  define NUMERIC_H

#  ifndef HAS_PRECOMPILED_STD_HEADERS
#     include <string>
#     include <iosfwd>
#  endif

#  include "ptypes.h"

#  ifdef CAT_BASE_LIB
#     ifdef CAT_BASE_IMPL
#        define NUMERIC_DECL_SPEC DYNAMIC_EXPORT
#     else
#        define NUMERIC_DECL_SPEC DYNAMIC_IMPORT
#     endif
#  else
#     define NUMERIC_DECL_SPEC
#  endif

const char c_decimal = '.';
const char c_separator = ',';

class read_stream;
class write_stream;

class NUMERIC_DECL_SPEC numeric
{
   class bool_test
   {
      public:
      bool_test( ) { }

      private:
      void operator delete( void* );
   };

   public:
   enum
   {
      e_max_digits = 19,
      e_default_decimals = 5
   };

   enum round_method
   {
      e_round_method_none,
      e_round_method_up,
      e_round_method_down,
      e_round_method_normal,
      e_round_method_bankers,
      e_round_method_truncate = e_round_method_down
   };

   numeric( )
    :
    decimals( 0 ),
    mantissa( 0 )
   {
   }

   numeric( int i );

   numeric( int64_t i );
   inline numeric( uint64_t ui ) : decimals( 0 ), mantissa( ui ) { }

   numeric( double d, int max_decimals = e_default_decimals, round_method method = e_round_method_normal );

   explicit numeric( const char* p, char dec = c_decimal, char sep = c_separator );

   numeric& round( int num_decimals = e_default_decimals, round_method method = e_round_method_normal );

   double frac( ) const;
   uint64_t trunc( ) const;

#  ifdef __BORLANDC__
   operator bool_test*( ) const;
#  else
   operator bool_test*( ) const
   {
      if( !mantissa )
         return 0;
      static bool_test test;
      return &test;
   }
#  endif

   numeric& operator ++( );
   numeric operator ++( int );

   numeric& operator --( );
   numeric operator --( int );

   numeric& operator +=( const numeric& n );
   numeric& operator -=( const numeric& n );
   numeric& operator *=( numeric n );
   numeric& operator /=( numeric n );

   std::string as_string( ) const;
   double as_double( ) const;

   inline uint64_t as_uint64( ) const { return mantissa; }

   std::string as_comparable_string( ) const;

   uint8_t digits( ) const;
   uint8_t whole_digits( ) const;

   inline uint8_t decimal_digits( ) const { return digits( ) - whole_digits( ); }

   static numeric max( );
   static numeric min( );

   static int max_digits( ) { return e_max_digits; }

   friend void NUMERIC_DECL_SPEC perform_add_or_subtract( numeric& n1, numeric n2, bool is_add );

   friend numeric NUMERIC_DECL_SPEC operator +( const numeric& lhs, const numeric& rhs );
   friend numeric NUMERIC_DECL_SPEC operator -( const numeric& lhs, const numeric& rhs );
   friend numeric NUMERIC_DECL_SPEC operator *( const numeric& lhs, const numeric& rhs );
   friend numeric NUMERIC_DECL_SPEC operator /( const numeric& lhs, const numeric& rhs );

   friend bool NUMERIC_DECL_SPEC operator <( const numeric& lhs, const numeric& rhs );
   friend bool NUMERIC_DECL_SPEC operator >( const numeric& lhs, const numeric& rhs );
   friend bool NUMERIC_DECL_SPEC operator <=( const numeric& lhs, const numeric& rhs );
   friend bool NUMERIC_DECL_SPEC operator >=( const numeric& lhs, const numeric& rhs );
   friend bool NUMERIC_DECL_SPEC operator !=( const numeric& lhs, const numeric& rhs );
   friend bool NUMERIC_DECL_SPEC operator ==( const numeric& lhs, const numeric& rhs );

   friend std::ostream NUMERIC_DECL_SPEC& operator <<( std::ostream& os, const numeric& f );

   friend read_stream NUMERIC_DECL_SPEC& operator >>( read_stream& rs, numeric& n );
   friend write_stream NUMERIC_DECL_SPEC& operator <<( write_stream& ws, const numeric& n );

   private:
   uint8_t decimals;
   uint64_t mantissa;

   void output_to_char_buffer( char* p_buf ) const;

   friend void level_decimals( numeric& n1, numeric& n2 );
};

#  ifdef __BORLANDC__
numeric::operator bool_test*( ) const
{
  if( !mantissa )
     return 0;
  static bool_test test;
  return &test;
}
#  endif

inline numeric& numeric::operator ++( )
{
   return operator +=( numeric( 1 ) );
}

inline numeric numeric::operator ++( int )
{
   numeric n( *this );

   ++*this;
   return n;
}

inline numeric& numeric::operator --( )
{
   return operator -=( numeric( 1 ) );
}

inline numeric numeric::operator --( int )
{
   numeric n( *this );

   --*this;
   return n;
}

inline numeric& numeric::operator +=( const numeric& n )
{
   perform_add_or_subtract( *this, n, true );

   return *this;
}

inline numeric& numeric::operator -=( const numeric& n )
{
   perform_add_or_subtract( *this, n, false );

   return *this;
}

inline numeric operator +( const numeric& lhs, const numeric& rhs )
{
   numeric n( lhs );
   n += rhs;
   return n;
}

inline numeric operator -( const numeric& lhs, const numeric& rhs )
{
   numeric n( lhs );
   n -= rhs;
   return n;
}

inline numeric operator *( const numeric& lhs, const numeric& rhs )
{
   numeric n( lhs );
   n *= rhs;
   return n;
}

inline numeric operator /( const numeric& lhs, const numeric& rhs )
{
   numeric n( lhs );
   n /= rhs;
   return n;
}

inline bool operator <=( const numeric& lhs, const numeric& rhs )
{
   return lhs == rhs ? true : lhs < rhs;
}

inline bool operator >=( const numeric& lhs, const numeric& rhs )
{
   return lhs == rhs ? true : lhs > rhs;
}

inline bool operator ==( const numeric& lhs, const numeric& rhs )
{
   return lhs.mantissa == rhs.mantissa && ( lhs.mantissa == 0 || lhs.decimals == rhs.decimals );
}

inline bool operator !=( const numeric& lhs, const numeric& rhs ) { return !( lhs == rhs ); }

std::string format_numeric( const numeric& n, const std::string& mask,
 const char* p_decimal_point = 0, const char* p_plus = 0, const char* p_minus = 0,
 const char* p_group_separator = 0, const char* p_plus_left = 0, const char* p_plus_right = 0,
 const char* p_minus_left = 0, const char* p_minus_right = 0, const char* p_currency_symbol = 0 );

#endif
