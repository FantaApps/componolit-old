with System;

package Nic_filter is

    procedure log(Num: Integer) with 
        Import,
        Convention => C,
        External_name => "_ZN15Nic_filter_test6Filter11hello_worldEi";
    procedure test(Num: Integer);

    procedure filter(
        dest: System.Address;
        src: System.Address;
        dest_size: Integer;
        src_size: Integer
        );

    private

    type char_array is array (integer range <>) of Character;

    procedure filter_spark (
        dest: out char_array;
        src: in char_array) with
        SPARK_Mode,
        Pre => (dest'Length = src'Length),
        Depends => (dest => src);

end Nic_filter;