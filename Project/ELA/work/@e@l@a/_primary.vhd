library verilog;
use verilog.vl_types.all;
entity ELA is
    generic(
        INIT            : integer := 0;
        PULL_REQ        : integer := 1;
        READ_GRAY       : integer := 2;
        ADD_ROW         : integer := 3;
        CHECK_LOC       : integer := 4;
        GET_TWO         : integer := 5;
        GET_SIX         : integer := 6;
        WRITE_RES       : integer := 7;
        FINISH          : integer := 8
    );
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        in_data         : in     vl_logic_vector(7 downto 0);
        data_rd         : in     vl_logic_vector(7 downto 0);
        req             : out    vl_logic;
        wen             : out    vl_logic;
        addr            : out    vl_logic_vector(9 downto 0);
        data_wr         : out    vl_logic_vector(7 downto 0);
        done            : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 1;
    attribute mti_svvh_generic_type of PULL_REQ : constant is 1;
    attribute mti_svvh_generic_type of READ_GRAY : constant is 1;
    attribute mti_svvh_generic_type of ADD_ROW : constant is 1;
    attribute mti_svvh_generic_type of CHECK_LOC : constant is 1;
    attribute mti_svvh_generic_type of GET_TWO : constant is 1;
    attribute mti_svvh_generic_type of GET_SIX : constant is 1;
    attribute mti_svvh_generic_type of WRITE_RES : constant is 1;
    attribute mti_svvh_generic_type of FINISH : constant is 1;
end ELA;
