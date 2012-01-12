// Copyright (c) 2008
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

#ifdef __BORLANDC__
#  include "precompile.h"
#endif
#pragma hdrstop

#ifndef HAS_PRECOMPILED_STD_HEADERS
#  include <cstring>
#  include <fstream>
#  include <iostream>
#  include <algorithm>
#  include <stdexcept>
#endif

#define CAT_BASE_LIB
#define MODULE_META_IMPL

// [<start macros>]
// [<finish macros>]

#include "Meta_Index.h"

#include "Meta_Class.h"
#include "Meta_Field.h"
#include "Meta_Index.h"

#include "cat_base.h"
#include "class_domains.h"
#include "module_strings.h"
#include "class_utilities.h"
#include "command_handler.h"
#include "module_interface.h"

// [(start clone_children_for_create)]
#include "Meta_Class.h"
// [(finish clone_children_for_create)]

// [<start includes>]
// [<finish includes>]

using namespace std;

// [<start namespaces>]
// [<finish namespaces>]

template< > inline string to_string( const Meta_Class& c )
{
   return ::to_string( static_cast< const class_base& >( c ) );
}

template< > inline string to_string( const Meta_Field& c )
{
   return ::to_string( static_cast< const class_base& >( c ) );
}

template< > inline string to_string( const Meta_Index& c )
{
   return ::to_string( static_cast< const class_base& >( c ) );
}

inline void from_string( Meta_Class& c, const string& s )
{
   ::from_string( static_cast< class_base& >( c ), s );
}

inline void from_string( Meta_Field& c, const string& s )
{
   ::from_string( static_cast< class_base& >( c ), s );
}

inline void from_string( Meta_Index& c, const string& s )
{
   ::from_string( static_cast< class_base& >( c ), s );
}

inline int system( const string& cmd ) { return exec_system( cmd ); }

namespace
{

#include "Meta_Index.cmh"

const int32_t c_version = 1;

const char* const c_okay = "okay";

const char* const c_field_id_Class = "300800";
const char* const c_field_id_Field_1 = "300811";
const char* const c_field_id_Field_2 = "300812";
const char* const c_field_id_Field_3 = "300813";
const char* const c_field_id_Field_4 = "300814";
const char* const c_field_id_Field_5 = "300815";
const char* const c_field_id_Internal = "108104";
const char* const c_field_id_Order = "108103";
const char* const c_field_id_Source_Index = "300820";
const char* const c_field_id_Unique = "108102";

const char* const c_field_name_Class = "Class";
const char* const c_field_name_Field_1 = "Field_1";
const char* const c_field_name_Field_2 = "Field_2";
const char* const c_field_name_Field_3 = "Field_3";
const char* const c_field_name_Field_4 = "Field_4";
const char* const c_field_name_Field_5 = "Field_5";
const char* const c_field_name_Internal = "Internal";
const char* const c_field_name_Order = "Order";
const char* const c_field_name_Source_Index = "Source_Index";
const char* const c_field_name_Unique = "Unique";

const char* const c_field_display_name_Class = "field_index_class";
const char* const c_field_display_name_Field_1 = "field_index_field_1";
const char* const c_field_display_name_Field_2 = "field_index_field_2";
const char* const c_field_display_name_Field_3 = "field_index_field_3";
const char* const c_field_display_name_Field_4 = "field_index_field_4";
const char* const c_field_display_name_Field_5 = "field_index_field_5";
const char* const c_field_display_name_Internal = "field_index_internal";
const char* const c_field_display_name_Order = "field_index_order";
const char* const c_field_display_name_Source_Index = "field_index_source_index";
const char* const c_field_display_name_Unique = "field_index_unique";

const int c_num_fields = 10;

const char* const c_all_sorted_field_ids[ ] =
{
   "108102",
   "108103",
   "108104",
   "300800",
   "300811",
   "300812",
   "300813",
   "300814",
   "300815",
   "300820"
};

const char* const c_all_sorted_field_names[ ] =
{
   "Class",
   "Field_1",
   "Field_2",
   "Field_3",
   "Field_4",
   "Field_5",
   "Internal",
   "Order",
   "Source_Index",
   "Unique"
};

inline bool compare( const char* p_s1, const char* p_s2 ) { return strcmp( p_s1, p_s2 ) < 0; }

inline bool has_field( const string& field )
{
   return binary_search( c_all_sorted_field_ids, c_all_sorted_field_ids + c_num_fields, field.c_str( ), compare )
    || binary_search( c_all_sorted_field_names, c_all_sorted_field_names + c_num_fields, field.c_str( ), compare );
}

const int c_num_transient_fields = 0;

bool is_transient_field( const string& ) { static bool false_value( false ); return false_value; }

const char* const c_procedure_id_Move_Down = "108420";
const char* const c_procedure_id_Move_Up = "108410";

const uint64_t c_modifier_Is_Internal = UINT64_C( 0x100 );

set< string > g_derivations;

typedef map< string, Meta_Index* > external_aliases_container;
typedef external_aliases_container::const_iterator external_aliases_const_iterator;
typedef external_aliases_container::value_type external_aliases_value_type;

typedef map< size_t, Meta_Index* > external_aliases_lookup_container;
typedef external_aliases_lookup_container::const_iterator external_aliases_lookup_const_iterator;

external_aliases_container g_external_aliases;
external_aliases_lookup_container g_external_aliases_lookup;

bool gv_default_Internal = bool( 0 );
string gv_default_Order = string( );
bool gv_default_Unique = bool( 1 );

// [<start anonymous>]
// [<finish anonymous>]

}

registration< Meta_Index > Index_registration( get_class_registry( ), "108100" );

class Meta_Index_command_functor;

class Meta_Index_command_handler : public command_handler
{
   friend class Meta_Index_command_functor;

   public:
   Meta_Index_command_handler( ) : p_Meta_Index( 0 ) { }

   void set_Meta_Index( Meta_Index* p_new_Meta_Index ) { p_Meta_Index = p_new_Meta_Index; }

   void handle_unknown_command( const string& command )
   {
      throw runtime_error( "unknown command '" + command + "'" );
   }

   void handle_invalid_command( const command_parser& parser, const string& cmd_and_args )
   {
      throw runtime_error( "invalid command usage '" + cmd_and_args + "'" );
   }

   private:
   Meta_Index* p_Meta_Index;

   protected:
   string retval;
};

class Meta_Index_command_functor : public command_functor
{
   public:
   Meta_Index_command_functor( Meta_Index_command_handler& handler )
    : command_functor( handler ),
    cmd_handler( handler )
   {
   }

   void operator ( )( const string& command, const parameter_info& parameters );

   private:
   Meta_Index_command_handler& cmd_handler;
};

command_functor* Meta_Index_command_functor_factory( const string& /*name*/, command_handler& handler )
{
   return new Meta_Index_command_functor( dynamic_cast< Meta_Index_command_handler& >( handler ) );
}

void Meta_Index_command_functor::operator ( )( const string& command, const parameter_info& parameters )
{
   if( command == c_cmd_Meta_Index_key )
   {
      bool want_fixed( has_parm_val( parameters, c_cmd_parm_Meta_Index_key_fixed ) );

      if( !want_fixed )
         cmd_handler.retval = cmd_handler.p_Meta_Index->get_key( );
      else
         cmd_handler.retval = cmd_handler.p_Meta_Index->get_fixed_key( );
   }
   else if( command == c_cmd_Meta_Index_ver )
   {
      string ver_rev( to_string( cmd_handler.p_Meta_Index->get_version( ) ) );
      ver_rev += "." + to_string( cmd_handler.p_Meta_Index->get_revision( ) );

      cmd_handler.retval = ver_rev;
   }
   else if( command == c_cmd_Meta_Index_get )
   {
      string field_name( get_parm_val( parameters, c_cmd_parm_Meta_Index_get_field_name ) );

      if( field_name.empty( ) )
         throw runtime_error( "field name must not be empty for getter call" );
      else if( field_name == c_field_id_Class || field_name == c_field_name_Class )
         string_getter< Meta_Class >( cmd_handler.p_Meta_Index->Class( ), cmd_handler.retval );
      else if( field_name == c_field_id_Field_1 || field_name == c_field_name_Field_1 )
         string_getter< Meta_Field >( cmd_handler.p_Meta_Index->Field_1( ), cmd_handler.retval );
      else if( field_name == c_field_id_Field_2 || field_name == c_field_name_Field_2 )
         string_getter< Meta_Field >( cmd_handler.p_Meta_Index->Field_2( ), cmd_handler.retval );
      else if( field_name == c_field_id_Field_3 || field_name == c_field_name_Field_3 )
         string_getter< Meta_Field >( cmd_handler.p_Meta_Index->Field_3( ), cmd_handler.retval );
      else if( field_name == c_field_id_Field_4 || field_name == c_field_name_Field_4 )
         string_getter< Meta_Field >( cmd_handler.p_Meta_Index->Field_4( ), cmd_handler.retval );
      else if( field_name == c_field_id_Field_5 || field_name == c_field_name_Field_5 )
         string_getter< Meta_Field >( cmd_handler.p_Meta_Index->Field_5( ), cmd_handler.retval );
      else if( field_name == c_field_id_Internal || field_name == c_field_name_Internal )
         string_getter< bool >( cmd_handler.p_Meta_Index->Internal( ), cmd_handler.retval );
      else if( field_name == c_field_id_Order || field_name == c_field_name_Order )
         string_getter< string >( cmd_handler.p_Meta_Index->Order( ), cmd_handler.retval );
      else if( field_name == c_field_id_Source_Index || field_name == c_field_name_Source_Index )
         string_getter< Meta_Index >( cmd_handler.p_Meta_Index->Source_Index( ), cmd_handler.retval );
      else if( field_name == c_field_id_Unique || field_name == c_field_name_Unique )
         string_getter< bool >( cmd_handler.p_Meta_Index->Unique( ), cmd_handler.retval );
      else
         throw runtime_error( "unknown field name '" + field_name + "' for getter call" );
   }
   else if( command == c_cmd_Meta_Index_set )
   {
      string field_name( get_parm_val( parameters, c_cmd_parm_Meta_Index_set_field_name ) );
      string field_value( get_parm_val( parameters, c_cmd_parm_Meta_Index_set_field_value ) );

      if( field_name.empty( ) )
         throw runtime_error( "field name must not be empty for setter call" );
      else if( field_name == c_field_id_Class || field_name == c_field_name_Class )
         func_string_setter< Meta_Index, Meta_Class >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Class, field_value );
      else if( field_name == c_field_id_Field_1 || field_name == c_field_name_Field_1 )
         func_string_setter< Meta_Index, Meta_Field >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Field_1, field_value );
      else if( field_name == c_field_id_Field_2 || field_name == c_field_name_Field_2 )
         func_string_setter< Meta_Index, Meta_Field >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Field_2, field_value );
      else if( field_name == c_field_id_Field_3 || field_name == c_field_name_Field_3 )
         func_string_setter< Meta_Index, Meta_Field >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Field_3, field_value );
      else if( field_name == c_field_id_Field_4 || field_name == c_field_name_Field_4 )
         func_string_setter< Meta_Index, Meta_Field >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Field_4, field_value );
      else if( field_name == c_field_id_Field_5 || field_name == c_field_name_Field_5 )
         func_string_setter< Meta_Index, Meta_Field >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Field_5, field_value );
      else if( field_name == c_field_id_Internal || field_name == c_field_name_Internal )
         func_string_setter< Meta_Index, bool >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Internal, field_value );
      else if( field_name == c_field_id_Order || field_name == c_field_name_Order )
         func_string_setter< Meta_Index, string >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Order, field_value );
      else if( field_name == c_field_id_Source_Index || field_name == c_field_name_Source_Index )
         func_string_setter< Meta_Index, Meta_Index >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Source_Index, field_value );
      else if( field_name == c_field_id_Unique || field_name == c_field_name_Unique )
         func_string_setter< Meta_Index, bool >(
          *cmd_handler.p_Meta_Index, &Meta_Index::Unique, field_value );
      else
         throw runtime_error( "unknown field name '" + field_name + "' for setter call" );

      cmd_handler.retval = c_okay;
   }
   else if( command == c_cmd_Meta_Index_cmd )
   {
      string field_name( get_parm_val( parameters, c_cmd_parm_Meta_Index_cmd_field_name ) );
      string cmd_and_args( get_parm_val( parameters, c_cmd_parm_Meta_Index_cmd_cmd_and_args ) );

      cmd_handler.retval.erase( );

      if( field_name.empty( ) )
         throw runtime_error( "field name must not be empty for command call" );
      else if( field_name == c_field_id_Class || field_name == c_field_name_Class )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Class( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Field_1 || field_name == c_field_name_Field_1 )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Field_1( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Field_2 || field_name == c_field_name_Field_2 )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Field_2( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Field_3 || field_name == c_field_name_Field_3 )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Field_3( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Field_4 || field_name == c_field_name_Field_4 )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Field_4( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Field_5 || field_name == c_field_name_Field_5 )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Field_5( ).execute( cmd_and_args );
      else if( field_name == c_field_id_Source_Index || field_name == c_field_name_Source_Index )
         cmd_handler.retval = cmd_handler.p_Meta_Index->Source_Index( ).execute( cmd_and_args );
      else
         throw runtime_error( "unknown field name '" + field_name + "' for command call" );
   }
   else if( command == c_cmd_Meta_Index_Move_Down )
   {
      string Restrict_Fields( get_parm_val_from_string< string >( parameters, c_cmd_parm_Meta_Index_Move_Down_Restrict_Fields ) );
      string Restrict_Values( get_parm_val_from_string< string >( parameters, c_cmd_parm_Meta_Index_Move_Down_Restrict_Values ) );
      cmd_handler.p_Meta_Index->Move_Down( Restrict_Fields, Restrict_Values );

      cmd_handler.retval.erase( );
   }
   else if( command == c_cmd_Meta_Index_Move_Up )
   {
      string Restrict_Fields( get_parm_val_from_string< string >( parameters, c_cmd_parm_Meta_Index_Move_Up_Restrict_Fields ) );
      string Restrict_Values( get_parm_val_from_string< string >( parameters, c_cmd_parm_Meta_Index_Move_Up_Restrict_Values ) );
      cmd_handler.p_Meta_Index->Move_Up( Restrict_Fields, Restrict_Values );

      cmd_handler.retval.erase( );
   }
}

struct Meta_Index::impl : public Meta_Index_command_handler
{
   impl( Meta_Index& o )
    :
    cp_obj( &o ),
    total_child_relationships( 0 )
   {
      p_obj = &o;
      set_Meta_Index( &o );

      add_commands( 0, Meta_Index_command_functor_factory,
       ARRAY_PTR_AND_SIZE( Meta_Index_command_definitions ) );
   }

   Meta_Index& get_obj( ) const
   {
      return *cp_obj;
   }

   bool impl_Internal( ) const { return lazy_fetch( p_obj ), v_Internal; }
   void impl_Internal( bool Internal ) { v_Internal = Internal; }

   const string& impl_Order( ) const { return lazy_fetch( p_obj ), v_Order; }
   void impl_Order( const string& Order ) { v_Order = Order; }

   bool impl_Unique( ) const { return lazy_fetch( p_obj ), v_Unique; }
   void impl_Unique( bool Unique ) { v_Unique = Unique; }

   Meta_Class& impl_Class( )
   {
      if( !cp_Class )
      {
         cp_Class.init( );

         p_obj->setup_graph_parent( *cp_Class, c_field_id_Class, v_Class );
      }
      return *cp_Class;
   }

   const Meta_Class& impl_Class( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Class )
      {
         cp_Class.init( );

         p_obj->setup_graph_parent( *cp_Class, c_field_id_Class, v_Class );
      }
      return *cp_Class;
   }

   void impl_Class( const string& key )
   {
      class_base_accessor cba( impl_Class( ) );
      cba.set_key( key );
   }

   Meta_Field& impl_Field_1( )
   {
      if( !cp_Field_1 )
      {
         cp_Field_1.init( );

         p_obj->setup_graph_parent( *cp_Field_1, c_field_id_Field_1, v_Field_1 );
      }
      return *cp_Field_1;
   }

   const Meta_Field& impl_Field_1( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Field_1 )
      {
         cp_Field_1.init( );

         p_obj->setup_graph_parent( *cp_Field_1, c_field_id_Field_1, v_Field_1 );
      }
      return *cp_Field_1;
   }

   void impl_Field_1( const string& key )
   {
      class_base_accessor cba( impl_Field_1( ) );
      cba.set_key( key );
   }

   Meta_Field& impl_Field_2( )
   {
      if( !cp_Field_2 )
      {
         cp_Field_2.init( );

         p_obj->setup_graph_parent( *cp_Field_2, c_field_id_Field_2, v_Field_2 );
      }
      return *cp_Field_2;
   }

   const Meta_Field& impl_Field_2( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Field_2 )
      {
         cp_Field_2.init( );

         p_obj->setup_graph_parent( *cp_Field_2, c_field_id_Field_2, v_Field_2 );
      }
      return *cp_Field_2;
   }

   void impl_Field_2( const string& key )
   {
      class_base_accessor cba( impl_Field_2( ) );
      cba.set_key( key );
   }

   Meta_Field& impl_Field_3( )
   {
      if( !cp_Field_3 )
      {
         cp_Field_3.init( );

         p_obj->setup_graph_parent( *cp_Field_3, c_field_id_Field_3, v_Field_3 );
      }
      return *cp_Field_3;
   }

   const Meta_Field& impl_Field_3( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Field_3 )
      {
         cp_Field_3.init( );

         p_obj->setup_graph_parent( *cp_Field_3, c_field_id_Field_3, v_Field_3 );
      }
      return *cp_Field_3;
   }

   void impl_Field_3( const string& key )
   {
      class_base_accessor cba( impl_Field_3( ) );
      cba.set_key( key );
   }

   Meta_Field& impl_Field_4( )
   {
      if( !cp_Field_4 )
      {
         cp_Field_4.init( );

         p_obj->setup_graph_parent( *cp_Field_4, c_field_id_Field_4, v_Field_4 );
      }
      return *cp_Field_4;
   }

   const Meta_Field& impl_Field_4( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Field_4 )
      {
         cp_Field_4.init( );

         p_obj->setup_graph_parent( *cp_Field_4, c_field_id_Field_4, v_Field_4 );
      }
      return *cp_Field_4;
   }

   void impl_Field_4( const string& key )
   {
      class_base_accessor cba( impl_Field_4( ) );
      cba.set_key( key );
   }

   Meta_Field& impl_Field_5( )
   {
      if( !cp_Field_5 )
      {
         cp_Field_5.init( );

         p_obj->setup_graph_parent( *cp_Field_5, c_field_id_Field_5, v_Field_5 );
      }
      return *cp_Field_5;
   }

   const Meta_Field& impl_Field_5( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Field_5 )
      {
         cp_Field_5.init( );

         p_obj->setup_graph_parent( *cp_Field_5, c_field_id_Field_5, v_Field_5 );
      }
      return *cp_Field_5;
   }

   void impl_Field_5( const string& key )
   {
      class_base_accessor cba( impl_Field_5( ) );
      cba.set_key( key );
   }

   Meta_Index& impl_Source_Index( )
   {
      if( !cp_Source_Index )
      {
         cp_Source_Index.init( );

         p_obj->setup_graph_parent( *cp_Source_Index, c_field_id_Source_Index, v_Source_Index );
      }
      return *cp_Source_Index;
   }

   const Meta_Index& impl_Source_Index( ) const
   {
      lazy_fetch( p_obj );

      if( !cp_Source_Index )
      {
         cp_Source_Index.init( );

         p_obj->setup_graph_parent( *cp_Source_Index, c_field_id_Source_Index, v_Source_Index );
      }
      return *cp_Source_Index;
   }

   void impl_Source_Index( const string& key )
   {
      class_base_accessor cba( impl_Source_Index( ) );
      cba.set_key( key );
   }

   Meta_Index& impl_child_Index_Source( )
   {
      if( !cp_child_Index_Source )
      {
         cp_child_Index_Source.init( );

         p_obj->setup_graph_parent( *cp_child_Index_Source, "300820" );
      }
      return *cp_child_Index_Source;
   }

   const Meta_Index& impl_child_Index_Source( ) const
   {
      if( !cp_child_Index_Source )
      {
         cp_child_Index_Source.init( );

         p_obj->setup_graph_parent( *cp_child_Index_Source, "300820" );
      }
      return *cp_child_Index_Source;
   }

   void impl_Move_Down( const string& Restrict_Fields, const string& Restrict_Values );

   void impl_Move_Up( const string& Restrict_Fields, const string& Restrict_Values );

   string get_field_value( int field ) const;
   void set_field_value( int field, const string& value );

   uint64_t get_state( ) const;

   const string& execute( const string& cmd_and_args );

   void clear_foreign_key( const string& field );

   void set_foreign_key_value( const string& field, const string& value );

   const string& get_foreign_key_value( const string& field );

   void get_foreign_key_values( foreign_key_data_container& foreign_key_values ) const;

   void clear( );

   bool value_will_be_provided( const string& field_name );

   void validate( unsigned state, bool is_internal, validation_error_container* p_validation_errors );

   void after_fetch( );
   void finalise_fetch( );

   void at_create( );

   void to_store( bool is_create, bool is_internal );
   void for_store( bool is_create, bool is_internal );
   void after_store( bool is_create, bool is_internal );

   bool can_destroy( bool is_internal );
   void for_destroy( bool is_internal );
   void after_destroy( bool is_internal );

   void set_default_values( );

   bool is_filtered( const set< string >& filters ) const;

   Meta_Index* p_obj;
   class_pointer< Meta_Index > cp_obj;

   // [<start members>]
   // [<finish members>]

   size_t total_child_relationships;

   bool v_Internal;
   string v_Order;
   bool v_Unique;

   string v_Class;
   mutable class_pointer< Meta_Class > cp_Class;

   string v_Field_1;
   mutable class_pointer< Meta_Field > cp_Field_1;

   string v_Field_2;
   mutable class_pointer< Meta_Field > cp_Field_2;

   string v_Field_3;
   mutable class_pointer< Meta_Field > cp_Field_3;

   string v_Field_4;
   mutable class_pointer< Meta_Field > cp_Field_4;

   string v_Field_5;
   mutable class_pointer< Meta_Field > cp_Field_5;

   string v_Source_Index;
   mutable class_pointer< Meta_Index > cp_Source_Index;

   mutable class_pointer< Meta_Index > cp_child_Index_Source;
};

void Meta_Index::impl::impl_Move_Down( const string& Restrict_Fields, const string& Restrict_Values )
{
   // [(start move_up_and_down)]
   transaction_start( );
   try
   {
      if( !Restrict_Fields.empty( ) )
      {
         get_obj( ).op_update( get_obj( ).get_key( ), c_field_name_Order );

         class_pointer< Meta_Index > cp_other( e_create_instance );

         int num_fixed = 0;
         if( !Restrict_Fields.empty( ) )
            num_fixed = split_count( Restrict_Fields );

         string key_info( Restrict_Fields );
         if( num_fixed )
            key_info += ',';
         key_info += string( c_field_id_Order );

         if( !num_fixed )
            key_info += ' ' + get_obj( ).Order( );
         else
         {
            key_info += '#' + to_string( num_fixed );
            key_info += ' ' + Restrict_Values + ',' + get_obj( ).Order( );
         }

         // NOTE: Only the first record is required so set the row limit to 1.
         if( cp_other->iterate_forwards( key_info, string( c_field_name_Order ), false, 1 ) )
         {
            string old_val( get_obj( ).Order( ) );
            string new_val( cp_other->Order( ) );

            get_obj( ).Order( gen_key( ) );
            get_obj( ).op_apply( );

            get_obj( ).op_update( get_obj( ).get_key( ), c_field_name_Order );

            cp_other->op_update( cp_other->get_key( ), c_field_name_Order );
            cp_other->Order( old_val );
            cp_other->op_apply( );

            get_obj( ).Order( new_val );
            get_obj( ).op_apply( );

            cp_other->iterate_stop( );
         }
         else
            get_obj( ).op_cancel( );
      }
      else
      {
         // NOTE: This code block exists to handle legacy transactions that can only pass empty strings
         // to the restrict fields/values. Newer models should not specify parent/extra fields in their
         // "move_up_and_down" specifications as they are not needed when using restrict fields/values.
         get_obj( ).op_update( get_obj( ).get_key( ) );

         Meta_Class parent;
         parent.perform_fetch( get_obj( ).Class( ) );

         string key_info( c_field_id_Order );
         key_info += ' ' + get_obj( ).Order( );
         // NOTE: Only the first record is required so set the row limit to 1.
         if( parent.child_Index( ).iterate_forwards( key_info, false, 1 ) )
         {
            string old_val( get_obj( ).Order( ) );
            string new_val( parent.child_Index( ).Order( ) );

            get_obj( ).Order( gen_key( ) );
            get_obj( ).op_apply( );

            get_obj( ).op_update( );

            parent.child_Index( ).op_update( );
            parent.child_Index( ).Order( old_val );
            parent.child_Index( ).op_apply( );

            get_obj( ).Order( new_val );
            get_obj( ).op_apply( );

            parent.child_Index( ).iterate_stop( );
         }
         else
            get_obj( ).op_cancel( );
      }

      transaction_commit( );
   }
   catch( ... )
   {
      transaction_rollback( );
      throw;
   }
   // [(finish move_up_and_down)]

   // [<start Move_Down_impl>]
   // [<finish Move_Down_impl>]
}

void Meta_Index::impl::impl_Move_Up( const string& Restrict_Fields, const string& Restrict_Values )
{
   // [(start move_up_and_down)]
   transaction_start( );
   try
   {
      if( !Restrict_Fields.empty( ) )
      {
         get_obj( ).op_update( get_obj( ).get_key( ), c_field_name_Order );

         class_pointer< Meta_Index > cp_other( e_create_instance );

         int num_fixed = 0;
         if( !Restrict_Fields.empty( ) )
            num_fixed = split_count( Restrict_Fields );

         string key_info( Restrict_Fields );
         if( num_fixed )
            key_info += ',';
         key_info += string( c_field_id_Order );

         if( !num_fixed )
            key_info += ' ' + get_obj( ).Order( );
         else
         {
            key_info += '#' + to_string( num_fixed );
            key_info += ' ' + Restrict_Values + ',' + get_obj( ).Order( );
         }

         // NOTE: Only the first record is required so set the row limit to 1.
         if( cp_other->iterate_backwards( key_info, string( c_field_name_Order ), false, 1 ) )
         {
            string old_val( get_obj( ).Order( ) );
            string new_val( cp_other->Order( ) );

            get_obj( ).Order( gen_key( ) );
            get_obj( ).op_apply( );

            get_obj( ).op_update( get_obj( ).get_key( ), c_field_name_Order );

            cp_other->op_update( cp_other->get_key( ), c_field_name_Order );
            cp_other->Order( old_val );
            cp_other->op_apply( );

            get_obj( ).Order( new_val );
            get_obj( ).op_apply( );

            cp_other->iterate_stop( );
         }
         else
            get_obj( ).op_cancel( );
      }
      else
      {
         // NOTE: This code block exists to handle legacy transactions that can only pass empty strings
         // to the restrict fields/values. Newer models should not specify parent/extra fields in their
         // "move_up_and_down" specifications as they are not needed when using restrict fields/values.
         get_obj( ).op_update( get_obj( ).get_key( ) );

         Meta_Class parent;
         parent.perform_fetch( get_obj( ).Class( ) );

         string key_info( c_field_id_Order );
         key_info += ' ' + get_obj( ).Order( );
         // NOTE: Only the first record is required so set the row limit to 1.
         if( parent.child_Index( ).iterate_backwards( key_info, false, 1 ) )
         {
            string old_val( get_obj( ).Order( ) );
            string new_val( parent.child_Index( ).Order( ) );

            get_obj( ).Order( gen_key( ) );
            get_obj( ).op_apply( );

            get_obj( ).op_update( );

            parent.child_Index( ).op_update( );
            parent.child_Index( ).Order( old_val );
            parent.child_Index( ).op_apply( );

            get_obj( ).Order( new_val );
            get_obj( ).op_apply( );

            parent.child_Index( ).iterate_stop( );
         }
         else
            get_obj( ).op_cancel( );
      }

      transaction_commit( );
   }
   catch( ... )
   {
      transaction_rollback( );
      throw;
   }
   // [(finish move_up_and_down)]

   // [<start Move_Up_impl>]
   // [<finish Move_Up_impl>]
}

string Meta_Index::impl::get_field_value( int field ) const
{
   string retval;

   switch( field )
   {
      case 0:
      retval = to_string( impl_Class( ) );
      break;

      case 1:
      retval = to_string( impl_Field_1( ) );
      break;

      case 2:
      retval = to_string( impl_Field_2( ) );
      break;

      case 3:
      retval = to_string( impl_Field_3( ) );
      break;

      case 4:
      retval = to_string( impl_Field_4( ) );
      break;

      case 5:
      retval = to_string( impl_Field_5( ) );
      break;

      case 6:
      retval = to_string( impl_Internal( ) );
      break;

      case 7:
      retval = to_string( impl_Order( ) );
      break;

      case 8:
      retval = to_string( impl_Source_Index( ) );
      break;

      case 9:
      retval = to_string( impl_Unique( ) );
      break;

      default:
      throw runtime_error( "field #" + to_string( field ) + " is out of range" );
   }

   return retval;
}

void Meta_Index::impl::set_field_value( int field, const string& value )
{
   switch( field )
   {
      case 0:
      func_string_setter< Meta_Index::impl, Meta_Class >( *this, &Meta_Index::impl::impl_Class, value );
      break;

      case 1:
      func_string_setter< Meta_Index::impl, Meta_Field >( *this, &Meta_Index::impl::impl_Field_1, value );
      break;

      case 2:
      func_string_setter< Meta_Index::impl, Meta_Field >( *this, &Meta_Index::impl::impl_Field_2, value );
      break;

      case 3:
      func_string_setter< Meta_Index::impl, Meta_Field >( *this, &Meta_Index::impl::impl_Field_3, value );
      break;

      case 4:
      func_string_setter< Meta_Index::impl, Meta_Field >( *this, &Meta_Index::impl::impl_Field_4, value );
      break;

      case 5:
      func_string_setter< Meta_Index::impl, Meta_Field >( *this, &Meta_Index::impl::impl_Field_5, value );
      break;

      case 6:
      func_string_setter< Meta_Index::impl, bool >( *this, &Meta_Index::impl::impl_Internal, value );
      break;

      case 7:
      func_string_setter< Meta_Index::impl, string >( *this, &Meta_Index::impl::impl_Order, value );
      break;

      case 8:
      func_string_setter< Meta_Index::impl, Meta_Index >( *this, &Meta_Index::impl::impl_Source_Index, value );
      break;

      case 9:
      func_string_setter< Meta_Index::impl, bool >( *this, &Meta_Index::impl::impl_Unique, value );
      break;

      default:
      throw runtime_error( "field #" + to_string( field ) + " is out of range" );
   }
}

uint64_t Meta_Index::impl::get_state( ) const
{
   uint64_t state = 0;

   // [(start modifier_field_value)]
   if( get_obj( ).Internal( ) == true )
      state |= c_modifier_Is_Internal;
   // [(finish modifier_field_value)]

   // [(start protect_equal)]
   if( check_equal( get_obj( ).Internal( ), true ) )
      state |= ( c_state_uneditable | c_state_undeletable );
   // [(finish protect_equal)]

   // [<start get_state>]
   // [<finish get_state>]

   return state;
}

const string& Meta_Index::impl::execute( const string& cmd_and_args )
{
   execute_command( cmd_and_args );
   return retval;
}

void Meta_Index::impl::clear_foreign_key( const string& field )
{
   if( field.empty( ) )
      throw runtime_error( "unexpected empty field name/id" );
   else if( field == c_field_id_Class || field == c_field_name_Class )
      impl_Class( "" );
   else if( field == c_field_id_Field_1 || field == c_field_name_Field_1 )
      impl_Field_1( "" );
   else if( field == c_field_id_Field_2 || field == c_field_name_Field_2 )
      impl_Field_2( "" );
   else if( field == c_field_id_Field_3 || field == c_field_name_Field_3 )
      impl_Field_3( "" );
   else if( field == c_field_id_Field_4 || field == c_field_name_Field_4 )
      impl_Field_4( "" );
   else if( field == c_field_id_Field_5 || field == c_field_name_Field_5 )
      impl_Field_5( "" );
   else if( field == c_field_id_Source_Index || field == c_field_name_Source_Index )
      impl_Source_Index( "" );
   else
      throw runtime_error( "unknown foreign key field '" + field + "'" );
}

void Meta_Index::impl::set_foreign_key_value( const string& field, const string& value )
{
   if( field.empty( ) )
      throw runtime_error( "unexpected empty field name/id for value: " + value );
   else if( field == c_field_id_Class || field == c_field_name_Class )
      v_Class = value;
   else if( field == c_field_id_Field_1 || field == c_field_name_Field_1 )
      v_Field_1 = value;
   else if( field == c_field_id_Field_2 || field == c_field_name_Field_2 )
      v_Field_2 = value;
   else if( field == c_field_id_Field_3 || field == c_field_name_Field_3 )
      v_Field_3 = value;
   else if( field == c_field_id_Field_4 || field == c_field_name_Field_4 )
      v_Field_4 = value;
   else if( field == c_field_id_Field_5 || field == c_field_name_Field_5 )
      v_Field_5 = value;
   else if( field == c_field_id_Source_Index || field == c_field_name_Source_Index )
      v_Source_Index = value;
   else
      throw runtime_error( "unknown foreign key field '" + field + "'" );
}

const string& Meta_Index::impl::get_foreign_key_value( const string& field )
{
   if( field.empty( ) )
      throw runtime_error( "unexpected empty field name/id" );
   else if( field == c_field_id_Class || field == c_field_name_Class )
      return v_Class;
   else if( field == c_field_id_Field_1 || field == c_field_name_Field_1 )
      return v_Field_1;
   else if( field == c_field_id_Field_2 || field == c_field_name_Field_2 )
      return v_Field_2;
   else if( field == c_field_id_Field_3 || field == c_field_name_Field_3 )
      return v_Field_3;
   else if( field == c_field_id_Field_4 || field == c_field_name_Field_4 )
      return v_Field_4;
   else if( field == c_field_id_Field_5 || field == c_field_name_Field_5 )
      return v_Field_5;
   else if( field == c_field_id_Source_Index || field == c_field_name_Source_Index )
      return v_Source_Index;
   else
      throw runtime_error( "unknown foreign key field '" + field + "'" );
}

void Meta_Index::impl::get_foreign_key_values( foreign_key_data_container& foreign_key_values ) const
{
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Class, v_Class ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Field_1, v_Field_1 ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Field_2, v_Field_2 ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Field_3, v_Field_3 ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Field_4, v_Field_4 ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Field_5, v_Field_5 ) );
   foreign_key_values.insert( foreign_key_data_value_type( c_field_id_Source_Index, v_Source_Index ) );
}

void Meta_Index::impl::clear( )
{
   v_Internal = gv_default_Internal;
   v_Order = gv_default_Order;
   v_Unique = gv_default_Unique;

   v_Class = string( );
   if( cp_Class )
      p_obj->setup_foreign_key( *cp_Class, v_Class );

   v_Field_1 = string( );
   if( cp_Field_1 )
      p_obj->setup_foreign_key( *cp_Field_1, v_Field_1 );

   v_Field_2 = string( );
   if( cp_Field_2 )
      p_obj->setup_foreign_key( *cp_Field_2, v_Field_2 );

   v_Field_3 = string( );
   if( cp_Field_3 )
      p_obj->setup_foreign_key( *cp_Field_3, v_Field_3 );

   v_Field_4 = string( );
   if( cp_Field_4 )
      p_obj->setup_foreign_key( *cp_Field_4, v_Field_4 );

   v_Field_5 = string( );
   if( cp_Field_5 )
      p_obj->setup_foreign_key( *cp_Field_5, v_Field_5 );

   v_Source_Index = string( );
   if( cp_Source_Index )
      p_obj->setup_foreign_key( *cp_Source_Index, v_Source_Index );
}

bool Meta_Index::impl::value_will_be_provided( const string& field_name )
{
   ( void )field_name;

   // [<start value_will_be_provided>]
   // [<finish value_will_be_provided>]

   return false;
}

void Meta_Index::impl::validate( unsigned state, bool is_internal, validation_error_container* p_validation_errors )
{
   ( void )state;
   ( void )is_internal;

   if( !p_validation_errors )
      throw runtime_error( "unexpected null validation_errors container" );

   if( is_null( v_Order ) && !value_will_be_provided( c_field_name_Order ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Order,
       get_string_message( GS( c_str_field_must_not_be_empty ), make_pair(
       c_str_parm_field_must_not_be_empty_field, get_module_string( c_field_display_name_Order ) ) ) ) );

   if( v_Class.empty( ) && !value_will_be_provided( c_field_name_Class ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Class,
       get_string_message( GS( c_str_field_must_not_be_empty ), make_pair(
       c_str_parm_field_must_not_be_empty_field, get_module_string( c_field_display_name_Class ) ) ) ) );

   if( v_Field_1.empty( ) && !value_will_be_provided( c_field_name_Field_1 ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Field_1,
       get_string_message( GS( c_str_field_must_not_be_empty ), make_pair(
       c_str_parm_field_must_not_be_empty_field, get_module_string( c_field_display_name_Field_1 ) ) ) ) );

   // [(start check_null_match)]
   if( is_null( get_obj( ).Field_2( ) ) && !is_null( get_obj( ).Field_3( ) ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Field_2,
       get_string_message( GS( c_str_field_must_be_empty_match ), make_pair(
       c_str_parm_field_must_be_empty_match_field2, get_module_string( c_field_display_name_Field_3 ) ),
       make_pair( c_str_parm_field_must_be_empty_match_field1, get_module_string( c_field_display_name_Field_2 ) ) ) ) );
   // [(finish check_null_match)]

   // [(start check_null_match)]
   if( is_null( get_obj( ).Field_3( ) ) && !is_null( get_obj( ).Field_4( ) ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Field_3,
       get_string_message( GS( c_str_field_must_be_empty_match ), make_pair(
       c_str_parm_field_must_be_empty_match_field2, get_module_string( c_field_display_name_Field_4 ) ),
       make_pair( c_str_parm_field_must_be_empty_match_field1, get_module_string( c_field_display_name_Field_3 ) ) ) ) );
   // [(finish check_null_match)]

   // [(start check_null_match)]
   if( is_null( get_obj( ).Field_4( ) ) && !is_null( get_obj( ).Field_5( ) ) )
      p_validation_errors->insert( validation_error_value_type( c_field_name_Field_4,
       get_string_message( GS( c_str_field_must_be_empty_match ), make_pair(
       c_str_parm_field_must_be_empty_match_field2, get_module_string( c_field_display_name_Field_5 ) ),
       make_pair( c_str_parm_field_must_be_empty_match_field1, get_module_string( c_field_display_name_Field_4 ) ) ) ) );
   // [(finish check_null_match)]

   // [(start check_no_repeats)]
   {
      size_t old_size = 0;
      set< string > values;
      vector< pair< string, string > > duplicate_fields;

      if( !is_null( get_obj( ).Field_1( ) ) )
      {
         values.insert( to_string( get_obj( ).Field_1( ) ) );
         if( values.size( ) > old_size )
            old_size = values.size( );
         else
            duplicate_fields.push_back( make_pair( c_field_name_Field_1, c_field_display_name_Field_1 ) );
      }

      if( !is_null( get_obj( ).Field_2( ) ) )
      {
         values.insert( to_string( get_obj( ).Field_2( ) ) );
         if( values.size( ) > old_size )
            old_size = values.size( );
         else
            duplicate_fields.push_back( make_pair( c_field_name_Field_2, c_field_display_name_Field_2 ) );
      }

      if( !is_null( get_obj( ).Field_3( ) ) )
      {
         values.insert( to_string( get_obj( ).Field_3( ) ) );
         if( values.size( ) > old_size )
            old_size = values.size( );
         else
            duplicate_fields.push_back( make_pair( c_field_name_Field_3, c_field_display_name_Field_3 ) );
      }

      if( !is_null( get_obj( ).Field_4( ) ) )
      {
         values.insert( to_string( get_obj( ).Field_4( ) ) );
         if( values.size( ) > old_size )
            old_size = values.size( );
         else
            duplicate_fields.push_back( make_pair( c_field_name_Field_4, c_field_display_name_Field_4 ) );
      }

      if( !is_null( get_obj( ).Field_5( ) ) )
      {
         values.insert( to_string( get_obj( ).Field_5( ) ) );
         if( values.size( ) > old_size )
            old_size = values.size( );
         else
            duplicate_fields.push_back( make_pair( c_field_name_Field_5, c_field_display_name_Field_5 ) );
      }

      for( size_t i = 0; i < duplicate_fields.size( ); i++ )
      {
         p_validation_errors->insert( validation_error_value_type( duplicate_fields[ i ].first,
          get_string_message( GS( c_str_invalid_duplicate_field_value ), make_pair(
          c_str_parm_invalid_duplicate_field_value_field, get_module_string( duplicate_fields[ i ].second ) ) ) ) );

      }
   }
   // [(finish check_no_repeats)]

   // [<start validate>]
   // [<finish validate>]
}

void Meta_Index::impl::after_fetch( )
{
   set< string > required_transients;

   p_obj->get_required_field_names( required_transients, true );

   if( cp_Class )
      p_obj->setup_foreign_key( *cp_Class, v_Class );

   if( cp_Field_1 )
      p_obj->setup_foreign_key( *cp_Field_1, v_Field_1 );

   if( cp_Field_2 )
      p_obj->setup_foreign_key( *cp_Field_2, v_Field_2 );

   if( cp_Field_3 )
      p_obj->setup_foreign_key( *cp_Field_3, v_Field_3 );

   if( cp_Field_4 )
      p_obj->setup_foreign_key( *cp_Field_4, v_Field_4 );

   if( cp_Field_5 )
      p_obj->setup_foreign_key( *cp_Field_5, v_Field_5 );

   if( cp_Source_Index )
      p_obj->setup_foreign_key( *cp_Source_Index, v_Source_Index );

   // [<start after_fetch>]
   // [<finish after_fetch>]
}

void Meta_Index::impl::finalise_fetch( )
{
   set< string > required_transients;

   p_obj->get_required_field_names( required_transients, true );

   // [<start finalise_fetch>]
   // [<finish finalise_fetch>]
}

void Meta_Index::impl::at_create( )
{
   // [<start at_create>]
   // [<finish at_create>]
}

void Meta_Index::impl::to_store( bool is_create, bool is_internal )
{
   ( void )is_create;
   ( void )is_internal;

   uint64_t state = p_obj->get_state( );
   ( void )state;

   // [(start default_from_key)]
   if( is_create && is_null( get_obj( ).Order( ) ) )
      get_obj( ).Order( get_obj( ).get_key( ) );
   // [(finish default_from_key)]

   // [(start field_empty_action)]
   if( !get_obj( ).get_key( ).empty( ) )
   {
      if( !is_null( get_obj( ).Class( ).Source_Class( ) ) )
         get_obj( ).Internal( true );
   }
   // [(finish field_empty_action)]

   // [<start to_store>]
   // [<finish to_store>]
}

void Meta_Index::impl::for_store( bool is_create, bool is_internal )
{
   ( void )is_create;
   ( void )is_internal;

   // [<start for_store>]
   // [<finish for_store>]
}

void Meta_Index::impl::after_store( bool is_create, bool is_internal )
{
   ( void )is_create;
   ( void )is_internal;

   // [(start clone_children_for_create)]
   if( is_create
    && get_obj( ).get_clone_key( ).empty( )
    && get_obj( ).Class( ).child_Class_Source( ).iterate_forwards( ) )
   {
      int child_num = 0;
      do
      {
         string key_info( construct_key_from_int( get_obj( ).get_key( ), ++child_num ) );
         key_info += ' ';
         key_info += get_obj( ).get_key( );

         get_obj( ).Class( ).child_Class_Source( ).child_Index( ).op_create( key_info );
         get_obj( ).Class( ).child_Class_Source( ).child_Index( ).Class( get_obj( ).Class( ).child_Class_Source( ).get_key( ) );
         get_obj( ).Class( ).child_Class_Source( ).child_Index( ).Source_Index( get_obj( ).get_key( ) );

         get_obj( ).Class( ).child_Class_Source( ).child_Index( ).op_apply( );
      } while( get_obj( ).Class( ).child_Class_Source( ).iterate_next( ) );
   }
   // [(finish clone_children_for_create)]

   // [(start clone_children_for_update)]
   if( !is_create && get_obj( ).child_Index_Source( ).iterate_forwards( ) )
   {
      do
      {
         get_obj( ).child_Index_Source( ).op_update( );
         string parent( get_obj( ).child_Index_Source( ).Class( ) );

         get_obj( ).child_Index_Source( ).copy_all_field_values( get_obj( ) );

         get_obj( ).child_Index_Source( ).Class( parent );
         get_obj( ).child_Index_Source( ).Source_Index( get_obj( ).get_key( ) );

         get_obj( ).child_Index_Source( ).op_apply( );
      } while( get_obj( ).child_Index_Source( ).iterate_next( ) );
   }
   // [(finish clone_children_for_update)]

   // [<start after_store>]
   // [<finish after_store>]
}

bool Meta_Index::impl::can_destroy( bool is_internal )
{
   bool retval = is_internal || !( get_state( ) & c_state_undeletable );

   // [<start can_destroy>]
   // [<finish can_destroy>]

   return retval;
}

void Meta_Index::impl::for_destroy( bool is_internal )
{
   ( void )is_internal;

   // [<start for_destroy>]
   // [<finish for_destroy>]
}

void Meta_Index::impl::after_destroy( bool is_internal )
{
   ( void )is_internal;

   // [<start after_destroy>]
   // [<finish after_destroy>]
}

void Meta_Index::impl::set_default_values( )
{
   clear( );
}

bool Meta_Index::impl::is_filtered( const set< string >& filters ) const
{
   ( void )filters;

   // [<start is_filtered>]
   // [<finish is_filtered>]

   return false;
}

#undef MODULE_TRACE
#define MODULE_TRACE( x ) trace( x )

Meta_Index::Meta_Index( )
{
   set_version( c_version );

   p_impl = new impl( *this );
}

Meta_Index::~Meta_Index( )
{
   cleanup( );
   delete p_impl;
}

bool Meta_Index::Internal( ) const
{
   return p_impl->impl_Internal( );
}

void Meta_Index::Internal( bool Internal )
{
   p_impl->impl_Internal( Internal );
}

const string& Meta_Index::Order( ) const
{
   return p_impl->impl_Order( );
}

void Meta_Index::Order( const string& Order )
{
   p_impl->impl_Order( Order );
}

bool Meta_Index::Unique( ) const
{
   return p_impl->impl_Unique( );
}

void Meta_Index::Unique( bool Unique )
{
   p_impl->impl_Unique( Unique );
}

Meta_Class& Meta_Index::Class( )
{
   return p_impl->impl_Class( );
}

const Meta_Class& Meta_Index::Class( ) const
{
   return p_impl->impl_Class( );
}

void Meta_Index::Class( const string& key )
{
   p_impl->impl_Class( key );
}

Meta_Field& Meta_Index::Field_1( )
{
   return p_impl->impl_Field_1( );
}

const Meta_Field& Meta_Index::Field_1( ) const
{
   return p_impl->impl_Field_1( );
}

void Meta_Index::Field_1( const string& key )
{
   p_impl->impl_Field_1( key );
}

Meta_Field& Meta_Index::Field_2( )
{
   return p_impl->impl_Field_2( );
}

const Meta_Field& Meta_Index::Field_2( ) const
{
   return p_impl->impl_Field_2( );
}

void Meta_Index::Field_2( const string& key )
{
   p_impl->impl_Field_2( key );
}

Meta_Field& Meta_Index::Field_3( )
{
   return p_impl->impl_Field_3( );
}

const Meta_Field& Meta_Index::Field_3( ) const
{
   return p_impl->impl_Field_3( );
}

void Meta_Index::Field_3( const string& key )
{
   p_impl->impl_Field_3( key );
}

Meta_Field& Meta_Index::Field_4( )
{
   return p_impl->impl_Field_4( );
}

const Meta_Field& Meta_Index::Field_4( ) const
{
   return p_impl->impl_Field_4( );
}

void Meta_Index::Field_4( const string& key )
{
   p_impl->impl_Field_4( key );
}

Meta_Field& Meta_Index::Field_5( )
{
   return p_impl->impl_Field_5( );
}

const Meta_Field& Meta_Index::Field_5( ) const
{
   return p_impl->impl_Field_5( );
}

void Meta_Index::Field_5( const string& key )
{
   p_impl->impl_Field_5( key );
}

Meta_Index& Meta_Index::Source_Index( )
{
   return p_impl->impl_Source_Index( );
}

const Meta_Index& Meta_Index::Source_Index( ) const
{
   return p_impl->impl_Source_Index( );
}

void Meta_Index::Source_Index( const string& key )
{
   p_impl->impl_Source_Index( key );
}

Meta_Index& Meta_Index::child_Index_Source( )
{
   return p_impl->impl_child_Index_Source( );
}

const Meta_Index& Meta_Index::child_Index_Source( ) const
{
   return p_impl->impl_child_Index_Source( );
}

void Meta_Index::Move_Down( const string& Restrict_Fields, const string& Restrict_Values )
{
   p_impl->impl_Move_Down( Restrict_Fields, Restrict_Values );
}

void Meta_Index::Move_Up( const string& Restrict_Fields, const string& Restrict_Values )
{
   p_impl->impl_Move_Up( Restrict_Fields, Restrict_Values );
}

string Meta_Index::get_field_value( int field ) const
{
   return p_impl->get_field_value( field );
}

void Meta_Index::set_field_value( int field, const string& value )
{
   p_impl->set_field_value( field, value );
}

bool Meta_Index::is_field_transient( int field ) const
{
   return static_is_field_transient( ( field_id )( field + 1 ) );
}

string Meta_Index::get_field_name( int field ) const
{
   return static_get_field_name( ( field_id )( field + 1 ) );
}

int Meta_Index::get_field_num( const string& field ) const
{
   int rc = static_get_field_num( field );

   if( rc < 0 )
      throw runtime_error( "unknown field name/id '" + field + "' in get_field_num( )" );

   return rc;
}

bool Meta_Index::has_field_changed( const string& field ) const
{
   return class_base::has_field_changed( get_field_num( field ) );
}

uint64_t Meta_Index::get_state( ) const
{
   uint64_t state = 0;

   state |= p_impl->get_state( );

   return state;
}

const string& Meta_Index::execute( const string& cmd_and_args )
{
   return p_impl->execute( cmd_and_args );
}

void Meta_Index::clear( )
{
   p_impl->clear( );
}

void Meta_Index::validate( unsigned state, bool is_internal )
{
   p_impl->validate( state, is_internal, &validation_errors );
}

void Meta_Index::after_fetch( )
{
   p_impl->after_fetch( );
}

void Meta_Index::finalise_fetch( )
{
   p_impl->finalise_fetch( );
}

void Meta_Index::at_create( )
{
   p_impl->at_create( );
}

void Meta_Index::to_store( bool is_create, bool is_internal )
{
   p_impl->to_store( is_create, is_internal );
}

void Meta_Index::for_store( bool is_create, bool is_internal )
{
   p_impl->for_store( is_create, is_internal );
}

void Meta_Index::after_store( bool is_create, bool is_internal )
{
   p_impl->after_store( is_create, is_internal );
}

bool Meta_Index::can_destroy( bool is_internal )
{
   return p_impl->can_destroy( is_internal );
}

void Meta_Index::for_destroy( bool is_internal )
{
   p_impl->for_destroy( is_internal );
}

void Meta_Index::after_destroy( bool is_internal )
{
   p_impl->after_destroy( is_internal );
}

void Meta_Index::set_default_values( )
{
   p_impl->set_default_values( );
}

bool Meta_Index::is_filtered( const set< string >& filters ) const
{
   return p_impl->is_filtered( filters );
}

const char* Meta_Index::get_field_id(
 const string& name, bool* p_sql_numeric, string* p_type_name ) const
{
   const char* p_id( 0 );

   if( name.empty( ) )
      throw runtime_error( "unexpected empty field name for get_field_id" );
   else if( name == c_field_name_Class )
   {
      p_id = c_field_id_Class;

      if( p_type_name )
         *p_type_name = "Meta_Class";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Field_1 )
   {
      p_id = c_field_id_Field_1;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Field_2 )
   {
      p_id = c_field_id_Field_2;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Field_3 )
   {
      p_id = c_field_id_Field_3;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Field_4 )
   {
      p_id = c_field_id_Field_4;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Field_5 )
   {
      p_id = c_field_id_Field_5;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Internal )
   {
      p_id = c_field_id_Internal;

      if( p_type_name )
         *p_type_name = "bool";

      if( p_sql_numeric )
         *p_sql_numeric = true;
   }
   else if( name == c_field_name_Order )
   {
      p_id = c_field_id_Order;

      if( p_type_name )
         *p_type_name = "string";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Source_Index )
   {
      p_id = c_field_id_Source_Index;

      if( p_type_name )
         *p_type_name = "Meta_Index";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( name == c_field_name_Unique )
   {
      p_id = c_field_id_Unique;

      if( p_type_name )
         *p_type_name = "bool";

      if( p_sql_numeric )
         *p_sql_numeric = true;
   }

   return p_id;
}

const char* Meta_Index::get_field_name(
 const string& id, bool* p_sql_numeric, string* p_type_name ) const
{
   const char* p_name( 0 );

   if( id.empty( ) )
      throw runtime_error( "unexpected empty field id for get_field_name" );
   else if( id == c_field_id_Class )
   {
      p_name = c_field_name_Class;

      if( p_type_name )
         *p_type_name = "Meta_Class";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Field_1 )
   {
      p_name = c_field_name_Field_1;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Field_2 )
   {
      p_name = c_field_name_Field_2;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Field_3 )
   {
      p_name = c_field_name_Field_3;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Field_4 )
   {
      p_name = c_field_name_Field_4;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Field_5 )
   {
      p_name = c_field_name_Field_5;

      if( p_type_name )
         *p_type_name = "Meta_Field";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Internal )
   {
      p_name = c_field_name_Internal;

      if( p_type_name )
         *p_type_name = "bool";

      if( p_sql_numeric )
         *p_sql_numeric = true;
   }
   else if( id == c_field_id_Order )
   {
      p_name = c_field_name_Order;

      if( p_type_name )
         *p_type_name = "string";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Source_Index )
   {
      p_name = c_field_name_Source_Index;

      if( p_type_name )
         *p_type_name = "Meta_Index";

      if( p_sql_numeric )
         *p_sql_numeric = false;
   }
   else if( id == c_field_id_Unique )
   {
      p_name = c_field_name_Unique;

      if( p_type_name )
         *p_type_name = "bool";

      if( p_sql_numeric )
         *p_sql_numeric = true;
   }

   return p_name;
}

string Meta_Index::get_field_display_name( const string& id ) const
{
   string display_name;

   if( id.empty( ) )
      throw runtime_error( "unexpected empty field id for get_field_display_name" );
   else if( id == c_field_id_Class )
      display_name = get_module_string( c_field_display_name_Class );
   else if( id == c_field_id_Field_1 )
      display_name = get_module_string( c_field_display_name_Field_1 );
   else if( id == c_field_id_Field_2 )
      display_name = get_module_string( c_field_display_name_Field_2 );
   else if( id == c_field_id_Field_3 )
      display_name = get_module_string( c_field_display_name_Field_3 );
   else if( id == c_field_id_Field_4 )
      display_name = get_module_string( c_field_display_name_Field_4 );
   else if( id == c_field_id_Field_5 )
      display_name = get_module_string( c_field_display_name_Field_5 );
   else if( id == c_field_id_Internal )
      display_name = get_module_string( c_field_display_name_Internal );
   else if( id == c_field_id_Order )
      display_name = get_module_string( c_field_display_name_Order );
   else if( id == c_field_id_Source_Index )
      display_name = get_module_string( c_field_display_name_Source_Index );
   else if( id == c_field_id_Unique )
      display_name = get_module_string( c_field_display_name_Unique );

   return display_name;
}

void Meta_Index::clear_foreign_key( const string& field )
{
   p_impl->clear_foreign_key( field );
}

void Meta_Index::set_foreign_key_value( const string& field, const string& value )
{
   p_impl->set_foreign_key_value( field, value );
}

const string& Meta_Index::get_foreign_key_value( const string& field )
{
   return p_impl->get_foreign_key_value( field );
}

void Meta_Index::get_foreign_key_values( foreign_key_data_container& foreign_key_values ) const
{
   p_impl->get_foreign_key_values( foreign_key_values );
}

void Meta_Index::setup_foreign_key( Meta_Class& o, const string& value )
{
   static_cast< Meta_Class& >( o ).set_key( value );
}

void Meta_Index::setup_foreign_key( Meta_Field& o, const string& value )
{
   static_cast< Meta_Field& >( o ).set_key( value );
}

void Meta_Index::setup_foreign_key( Meta_Index& o, const string& value )
{
   static_cast< Meta_Index& >( o ).set_key( value );
}

void Meta_Index::setup_graph_parent( Meta_Index& o, const string& foreign_key_field )
{
   static_cast< Meta_Index& >( o ).set_graph_parent( this, foreign_key_field );
}

void Meta_Index::setup_graph_parent(
 Meta_Class& o, const string& foreign_key_field, const string& init_value )
{
   static_cast< Meta_Class& >( o ).set_graph_parent( this, foreign_key_field, true );
   static_cast< Meta_Class& >( o ).set_key( init_value );
}

void Meta_Index::setup_graph_parent(
 Meta_Field& o, const string& foreign_key_field, const string& init_value )
{
   static_cast< Meta_Field& >( o ).set_graph_parent( this, foreign_key_field, true );
   static_cast< Meta_Field& >( o ).set_key( init_value );
}

void Meta_Index::setup_graph_parent(
 Meta_Index& o, const string& foreign_key_field, const string& init_value )
{
   static_cast< Meta_Index& >( o ).set_graph_parent( this, foreign_key_field, true );
   static_cast< Meta_Index& >( o ).set_key( init_value );
}

size_t Meta_Index::get_total_child_relationships( ) const
{
   return p_impl->total_child_relationships;
}

void Meta_Index::set_total_child_relationships( size_t new_total_child_relationships ) const
{
   p_impl->total_child_relationships = new_total_child_relationships;
}

size_t Meta_Index::get_num_foreign_key_children( bool is_internal ) const
{
   size_t rc = 1;

   if( !is_internal )
   {
      g_external_aliases_lookup.clear( );

      for( external_aliases_const_iterator
       eaci = g_external_aliases.begin( ), end = g_external_aliases.end( ); eaci != end; ++eaci )
      {
         size_t num_extra = eaci->second->get_num_foreign_key_children( true );

         if( num_extra )
         {
            eaci->second->set_key( get_key( ) );
            eaci->second->copy_all_field_values( *this );

            g_external_aliases_lookup.insert( make_pair( rc, eaci->second ) );

            rc += num_extra;
         }
      }
   }

   set_total_child_relationships( rc );

   return rc;
}

class_base* Meta_Index::get_next_foreign_key_child(
 size_t child_num, string& next_child_field, cascade_op op, bool is_internal )
{
   class_base* p_class_base = 0;

   if( child_num >= 1 )
   {
      external_aliases_lookup_const_iterator ealci = g_external_aliases_lookup.lower_bound( child_num );
      if( ealci == g_external_aliases_lookup.end( ) || ealci->first > child_num )
         --ealci;

      p_class_base = ealci->second->get_next_foreign_key_child( child_num - ealci->first, next_child_field, op, true );
   }
   else
   {
      switch( child_num )
      {
         case 0:
         if( op == e_cascade_op_destroy )
         {
            next_child_field = "300820";
            p_class_base = &child_Index_Source( );
         }
         break;
      }
   }

   return p_class_base;
}

const char* Meta_Index::class_id( ) const
{
   return static_class_id( );
}

const char* Meta_Index::class_name( ) const
{
   return static_class_name( );
}

const char* Meta_Index::plural_name( ) const
{
   return static_plural_name( );
}

const char* Meta_Index::module_id( ) const
{
   return static_module_id( );
}

const char* Meta_Index::module_name( ) const
{
   return static_module_name( );
}

string Meta_Index::get_display_name( bool plural ) const
{
   string key( plural ? "plural_" : "class_" );
   key += "index";

   return get_module_string( key );
}

bool Meta_Index::get_is_alias( ) const
{
   return false;
}

void Meta_Index::get_alias_base_info( pair< string, string >& alias_base_info ) const
{
   ( void )alias_base_info;
}

void Meta_Index::get_base_class_info( vector< pair< string, string > >& base_class_info ) const
{
   ( void )base_class_info;
}

class_base& Meta_Index::get_or_create_graph_child( const string& context )
{
   class_base* p_class_base( 0 );

   string::size_type pos = context.find( '.' );
   string sub_context( context.substr( 0, pos ) );

   if( sub_context.empty( ) )
      throw runtime_error( "unexpected empty sub-context" );
   else if( sub_context == "_300820" || sub_context == "child_Index_Source" )
      p_class_base = &child_Index_Source( );
   else if( sub_context == c_field_id_Class || sub_context == c_field_name_Class )
      p_class_base = &Class( );
   else if( sub_context == c_field_id_Field_1 || sub_context == c_field_name_Field_1 )
      p_class_base = &Field_1( );
   else if( sub_context == c_field_id_Field_2 || sub_context == c_field_name_Field_2 )
      p_class_base = &Field_2( );
   else if( sub_context == c_field_id_Field_3 || sub_context == c_field_name_Field_3 )
      p_class_base = &Field_3( );
   else if( sub_context == c_field_id_Field_4 || sub_context == c_field_name_Field_4 )
      p_class_base = &Field_4( );
   else if( sub_context == c_field_id_Field_5 || sub_context == c_field_name_Field_5 )
      p_class_base = &Field_5( );
   else if( sub_context == c_field_id_Source_Index || sub_context == c_field_name_Source_Index )
      p_class_base = &Source_Index( );

   if( !p_class_base )
      throw runtime_error( "unknown sub-context '" + sub_context + "'" );

   if( pos != string::npos )
      p_class_base = &p_class_base->get_or_create_graph_child( context.substr( pos + 1 ) );

   return *p_class_base;
}

void Meta_Index::get_sql_column_names(
 vector< string >& names, bool* p_done, const string* p_class_name ) const
{
   if( p_done && *p_done )
      return;

   names.push_back( "C_Class" );
   names.push_back( "C_Field_1" );
   names.push_back( "C_Field_2" );
   names.push_back( "C_Field_3" );
   names.push_back( "C_Field_4" );
   names.push_back( "C_Field_5" );
   names.push_back( "C_Internal" );
   names.push_back( "C_Order" );
   names.push_back( "C_Source_Index" );
   names.push_back( "C_Unique" );

   if( p_done && p_class_name && *p_class_name == static_class_name( ) )
      *p_done = true;
}

void Meta_Index::get_sql_column_values(
 vector< string >& values, bool* p_done, const string* p_class_name ) const
{
   if( p_done && *p_done )
      return;

   values.push_back( sql_quote( to_string( Class( ) ) ) );
   values.push_back( sql_quote( to_string( Field_1( ) ) ) );
   values.push_back( sql_quote( to_string( Field_2( ) ) ) );
   values.push_back( sql_quote( to_string( Field_3( ) ) ) );
   values.push_back( sql_quote( to_string( Field_4( ) ) ) );
   values.push_back( sql_quote( to_string( Field_5( ) ) ) );
   values.push_back( to_string( Internal( ) ) );
   values.push_back( sql_quote( to_string( Order( ) ) ) );
   values.push_back( sql_quote( to_string( Source_Index( ) ) ) );
   values.push_back( to_string( Unique( ) ) );

   if( p_done && p_class_name && *p_class_name == static_class_name( ) )
      *p_done = true;
}

void Meta_Index::get_required_field_names(
 set< string >& names, bool required_transients, set< string >* p_dependents ) const
{
   set< string > local_dependents;
   set< string >& dependents( p_dependents ? *p_dependents : local_dependents );

   get_always_required_field_names( names, required_transients, dependents );

   // [<start get_required_field_names>]
   // [<finish get_required_field_names>]
}

void Meta_Index::get_always_required_field_names(
 set< string >& names, bool required_transients, set< string >& dependents ) const
{
   ( void )names;
   ( void )dependents;
   ( void )required_transients;

   // [(start move_up_and_down)]
   dependents.insert( "Order" );

   if( ( required_transients && is_field_transient( e_field_id_Order ) )
    || ( !required_transients && !is_field_transient( e_field_id_Order ) ) )
      names.insert( "Order" );
   // [(finish move_up_and_down)]

   // [(start modifier_field_value)]
   dependents.insert( "Internal" ); // (for Is_Internal modifier)

   if( ( required_transients && is_field_transient( e_field_id_Internal ) )
    || ( !required_transients && !is_field_transient( e_field_id_Internal ) ) )
      names.insert( "Internal" );
   // [(finish modifier_field_value)]

   // [(start protect_equal)]
   dependents.insert( "Internal" );

   if( ( required_transients && is_field_transient( e_field_id_Internal ) )
    || ( !required_transients && !is_field_transient( e_field_id_Internal ) ) )
      names.insert( "Internal" );
   // [(finish protect_equal)]

   // [<start get_always_required_field_names>]


   // [<finish get_always_required_field_names>]
}

void Meta_Index::get_transient_replacement_field_names( const string& name, vector< string >& names ) const
{
   ( void )name;
   ( void )names;

   // [<start get_transient_replacement_field_names>]
   // [<finish get_transient_replacement_field_names>]
}

void Meta_Index::do_generate_sql( generate_sql_type type, vector< string >& sql_stmts ) const
{
   generate_sql( static_class_name( ), type, sql_stmts );
}

const char* Meta_Index::static_resolved_module_id( )
{
   return static_module_id( );
}

const char* Meta_Index::static_resolved_module_name( )
{
   return static_module_name( );
}

const char* Meta_Index::static_lock_class_id( )
{
   return "108100";
}

const char* Meta_Index::static_check_class_name( )
{
   return "Index";
}

bool Meta_Index::static_has_derivations( )
{
   return !g_derivations.empty( );
}

void Meta_Index::static_get_class_info( class_info_container& class_info )
{
   class_info.push_back( "100.108100" );
}

void Meta_Index::static_get_field_info( field_info_container& all_field_info )
{
   all_field_info.push_back( field_info( "300800", "Class", "Meta_Class", true ) );
   all_field_info.push_back( field_info( "300811", "Field_1", "Meta_Field", true ) );
   all_field_info.push_back( field_info( "300812", "Field_2", "Meta_Field", false ) );
   all_field_info.push_back( field_info( "300813", "Field_3", "Meta_Field", false ) );
   all_field_info.push_back( field_info( "300814", "Field_4", "Meta_Field", false ) );
   all_field_info.push_back( field_info( "300815", "Field_5", "Meta_Field", false ) );
   all_field_info.push_back( field_info( "108104", "Internal", "bool", false ) );
   all_field_info.push_back( field_info( "108103", "Order", "string", false ) );
   all_field_info.push_back( field_info( "300820", "Source_Index", "Meta_Index", false ) );
   all_field_info.push_back( field_info( "108102", "Unique", "bool", false ) );
}

void Meta_Index::static_get_foreign_key_info( foreign_key_info_container& foreign_key_info )
{
   ( void )foreign_key_info;

   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Class, make_pair( "Meta.108100", "Meta_Class" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Field_1, make_pair( "Meta.108100", "Meta_Field" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Field_2, make_pair( "Meta.108100", "Meta_Field" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Field_3, make_pair( "Meta.108100", "Meta_Field" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Field_4, make_pair( "Meta.108100", "Meta_Field" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Field_5, make_pair( "Meta.108100", "Meta_Field" ) ) );
   foreign_key_info.insert( foreign_key_info_value_type( c_field_id_Source_Index, make_pair( "Meta.108100", "Meta_Index" ) ) );
}

int Meta_Index::static_get_num_fields( bool* p_done, const string* p_class_name )
{
   if( p_done && p_class_name && *p_class_name == static_class_name( ) )
      *p_done = true;

   return c_num_fields;
}

bool Meta_Index::static_is_field_transient( field_id id )
{
   return is_transient_field( static_get_field_id( id ) );
}

const char* Meta_Index::static_get_field_id( field_id id )
{
   const char* p_id = 0;

   switch( id )
   {
      case 1:
      p_id = "300800";
      break;

      case 2:
      p_id = "300811";
      break;

      case 3:
      p_id = "300812";
      break;

      case 4:
      p_id = "300813";
      break;

      case 5:
      p_id = "300814";
      break;

      case 6:
      p_id = "300815";
      break;

      case 7:
      p_id = "108104";
      break;

      case 8:
      p_id = "108103";
      break;

      case 9:
      p_id = "300820";
      break;

      case 10:
      p_id = "108102";
      break;
   }

   if( !p_id )
      throw runtime_error( "unknown field id #" + to_string( id ) + " for class Index" );

   return p_id;
}

const char* Meta_Index::static_get_field_name( field_id id )
{
   const char* p_id = 0;

   switch( id )
   {
      case 1:
      p_id = "Class";
      break;

      case 2:
      p_id = "Field_1";
      break;

      case 3:
      p_id = "Field_2";
      break;

      case 4:
      p_id = "Field_3";
      break;

      case 5:
      p_id = "Field_4";
      break;

      case 6:
      p_id = "Field_5";
      break;

      case 7:
      p_id = "Internal";
      break;

      case 8:
      p_id = "Order";
      break;

      case 9:
      p_id = "Source_Index";
      break;

      case 10:
      p_id = "Unique";
      break;
   }

   if( !p_id )
      throw runtime_error( "unknown field id #" + to_string( id ) + " for class Index" );

   return p_id;
}

int Meta_Index::static_get_field_num( const string& field )
{
   int rc = 0;

   if( field.empty( ) )
      throw runtime_error( "unexpected empty field name/id for static_get_field_num( )" );
   else if( field == c_field_id_Class || field == c_field_name_Class )
      rc += 1;
   else if( field == c_field_id_Field_1 || field == c_field_name_Field_1 )
      rc += 2;
   else if( field == c_field_id_Field_2 || field == c_field_name_Field_2 )
      rc += 3;
   else if( field == c_field_id_Field_3 || field == c_field_name_Field_3 )
      rc += 4;
   else if( field == c_field_id_Field_4 || field == c_field_name_Field_4 )
      rc += 5;
   else if( field == c_field_id_Field_5 || field == c_field_name_Field_5 )
      rc += 6;
   else if( field == c_field_id_Internal || field == c_field_name_Internal )
      rc += 7;
   else if( field == c_field_id_Order || field == c_field_name_Order )
      rc += 8;
   else if( field == c_field_id_Source_Index || field == c_field_name_Source_Index )
      rc += 9;
   else if( field == c_field_id_Unique || field == c_field_name_Unique )
      rc += 10;

   return rc - 1;
}

procedure_info_container& Meta_Index::static_get_procedure_info( )
{
   static bool initialised = false;
   static procedure_info_container procedures;

   if( !initialised )
   {
      initialised = true;
      procedures.insert( make_pair( "108420", "Move_Down" ) );
      procedures.insert( make_pair( "108410", "Move_Up" ) );
   }

   return procedures;
}

string Meta_Index::static_get_sql_columns( )
{
   string sql_columns;

   sql_columns += 
    "C_Key_ VARCHAR(64),"
    "C_Ver_ INTEGER NOT NULL,"
    "C_Rev_ INTEGER NOT NULL,"
    "C_Typ_ VARCHAR(24) NOT NULL,"
    "C_Class VARCHAR(64) NOT NULL,"
    "C_Field_1 VARCHAR(64) NOT NULL,"
    "C_Field_2 VARCHAR(64) NOT NULL,"
    "C_Field_3 VARCHAR(64) NOT NULL,"
    "C_Field_4 VARCHAR(64) NOT NULL,"
    "C_Field_5 VARCHAR(64) NOT NULL,"
    "C_Internal INTEGER NOT NULL,"
    "C_Order VARCHAR(128) NOT NULL,"
    "C_Source_Index VARCHAR(64) NOT NULL,"
    "C_Unique INTEGER NOT NULL,"
    "PRIMARY KEY(C_Key_)";

   return sql_columns;
}

void Meta_Index::static_get_text_search_fields( vector< string >& fields )
{
   ( void )fields;
}

void Meta_Index::static_get_all_enum_pairs( vector< pair< string, string > >& pairs )
{
   ( void )pairs;
}

void Meta_Index::static_get_sql_indexes( vector< string >& indexes )
{
   indexes.push_back( "C_Class,C_Order" );
}

void Meta_Index::static_get_sql_unique_indexes( vector< string >& indexes )
{
   indexes.push_back( "C_Class,C_Order" );
}

void Meta_Index::static_insert_derivation( const string& module_and_class_id )
{
   g_derivations.insert( module_and_class_id );
}

void Meta_Index::static_remove_derivation( const string& module_and_class_id )
{
   if( g_derivations.count( module_and_class_id ) )
      g_derivations.erase( module_and_class_id );
}

void Meta_Index::static_insert_external_alias( const string& module_and_class_id, Meta_Index* p_instance )
{
   g_external_aliases.insert( external_aliases_value_type( module_and_class_id, p_instance ) );
}

void Meta_Index::static_remove_external_alias( const string& module_and_class_id )
{
   if( g_external_aliases.count( module_and_class_id ) )
   {
      delete g_external_aliases[ module_and_class_id ];
      g_external_aliases.erase( module_and_class_id );
   }
}

void Meta_Index::static_class_init( const char* p_module_name )
{
   if( !p_module_name )
      throw runtime_error( "unexpected null module name pointer for init" );

   // [<start static_class_init>]
   // [<finish static_class_init>]
}

void Meta_Index::static_class_term( const char* p_module_name )
{
   if( !p_module_name )
      throw runtime_error( "unexpected null module name pointer for term" );

   // [<start static_class_term>]
   // [<finish static_class_term>]
}
