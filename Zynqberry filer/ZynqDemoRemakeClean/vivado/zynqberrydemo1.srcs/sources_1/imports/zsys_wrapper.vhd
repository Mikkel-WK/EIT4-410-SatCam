--Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
--Date        : Fri Mar  4 13:25:28 2022
--Host        : DESKTOP-LNVH2M6 running 64-bit major release  (build 9200)
--Command     : generate_target zsys_wrapper.bd
--Design      : zsys_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zsys_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    GPIO_1_tri_io : inout STD_LOGIC_VECTOR ( 23 downto 0 );
    PWM_L : out STD_LOGIC;
    PWM_R : out STD_LOGIC;
    Vp_Vn_v_n : in STD_LOGIC;
    Vp_Vn_v_p : in STD_LOGIC;
    csi_c_clk_n : in STD_LOGIC;
    csi_c_clk_p : in STD_LOGIC;
    csi_d_lp_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    csi_d_lp_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    csi_d_n : in STD_LOGIC_VECTOR ( 1 downto 0 );
    csi_d_p : in STD_LOGIC_VECTOR ( 1 downto 0 );
    hdmi_clk_n : out STD_LOGIC;
    hdmi_clk_p : out STD_LOGIC;
    hdmi_data_n : out STD_LOGIC_VECTOR ( 2 downto 0 );
    hdmi_data_p : out STD_LOGIC_VECTOR ( 2 downto 0 )
  );
end zsys_wrapper;

architecture STRUCTURE of zsys_wrapper is
  component zsys is
  port (
    PWM_L : out STD_LOGIC;
    PWM_R : out STD_LOGIC;
    csi_c_clk_n : in STD_LOGIC;
    csi_c_clk_p : in STD_LOGIC;
    csi_d_lp_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    csi_d_lp_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    csi_d_n : in STD_LOGIC_VECTOR ( 1 downto 0 );
    csi_d_p : in STD_LOGIC_VECTOR ( 1 downto 0 );
    hdmi_clk_n : out STD_LOGIC;
    hdmi_clk_p : out STD_LOGIC;
    hdmi_data_n : out STD_LOGIC_VECTOR ( 2 downto 0 );
    hdmi_data_p : out STD_LOGIC_VECTOR ( 2 downto 0 );
    Vp_Vn_v_n : in STD_LOGIC;
    Vp_Vn_v_p : in STD_LOGIC;
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    GPIO_1_tri_i : in STD_LOGIC_VECTOR ( 23 downto 0 );
    GPIO_1_tri_o : out STD_LOGIC_VECTOR ( 23 downto 0 );
    GPIO_1_tri_t : out STD_LOGIC_VECTOR ( 23 downto 0 )
  );
  end component zsys;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal GPIO_1_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_1_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_1_tri_i_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_1_tri_i_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_1_tri_i_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_1_tri_i_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_1_tri_i_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_1_tri_i_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_1_tri_i_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_1_tri_i_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_1_tri_i_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_1_tri_i_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_1_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_1_tri_i_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_1_tri_i_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_1_tri_i_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_1_tri_i_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_1_tri_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_1_tri_i_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_1_tri_i_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_1_tri_i_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_1_tri_i_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_1_tri_i_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_1_tri_i_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_1_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_1_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_1_tri_io_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_1_tri_io_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_1_tri_io_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_1_tri_io_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_1_tri_io_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_1_tri_io_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_1_tri_io_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_1_tri_io_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_1_tri_io_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_1_tri_io_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_1_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_1_tri_io_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_1_tri_io_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_1_tri_io_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_1_tri_io_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_1_tri_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_1_tri_io_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_1_tri_io_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_1_tri_io_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_1_tri_io_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_1_tri_io_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_1_tri_io_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_1_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_1_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_1_tri_o_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_1_tri_o_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_1_tri_o_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_1_tri_o_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_1_tri_o_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_1_tri_o_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_1_tri_o_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_1_tri_o_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_1_tri_o_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_1_tri_o_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_1_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_1_tri_o_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_1_tri_o_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_1_tri_o_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_1_tri_o_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_1_tri_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_1_tri_o_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_1_tri_o_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_1_tri_o_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_1_tri_o_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_1_tri_o_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_1_tri_o_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_1_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_1_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_1_tri_t_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_1_tri_t_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_1_tri_t_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_1_tri_t_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_1_tri_t_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_1_tri_t_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_1_tri_t_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_1_tri_t_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_1_tri_t_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_1_tri_t_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_1_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_1_tri_t_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_1_tri_t_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_1_tri_t_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_1_tri_t_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_1_tri_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_1_tri_t_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_1_tri_t_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_1_tri_t_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_1_tri_t_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_1_tri_t_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_1_tri_t_9 : STD_LOGIC_VECTOR ( 9 to 9 );
begin
GPIO_1_tri_iobuf_0: component IOBUF
     port map (
      I => GPIO_1_tri_o_0(0),
      IO => GPIO_1_tri_io(0),
      O => GPIO_1_tri_i_0(0),
      T => GPIO_1_tri_t_0(0)
    );
GPIO_1_tri_iobuf_1: component IOBUF
     port map (
      I => GPIO_1_tri_o_1(1),
      IO => GPIO_1_tri_io(1),
      O => GPIO_1_tri_i_1(1),
      T => GPIO_1_tri_t_1(1)
    );
GPIO_1_tri_iobuf_10: component IOBUF
     port map (
      I => GPIO_1_tri_o_10(10),
      IO => GPIO_1_tri_io(10),
      O => GPIO_1_tri_i_10(10),
      T => GPIO_1_tri_t_10(10)
    );
GPIO_1_tri_iobuf_11: component IOBUF
     port map (
      I => GPIO_1_tri_o_11(11),
      IO => GPIO_1_tri_io(11),
      O => GPIO_1_tri_i_11(11),
      T => GPIO_1_tri_t_11(11)
    );
GPIO_1_tri_iobuf_12: component IOBUF
     port map (
      I => GPIO_1_tri_o_12(12),
      IO => GPIO_1_tri_io(12),
      O => GPIO_1_tri_i_12(12),
      T => GPIO_1_tri_t_12(12)
    );
GPIO_1_tri_iobuf_13: component IOBUF
     port map (
      I => GPIO_1_tri_o_13(13),
      IO => GPIO_1_tri_io(13),
      O => GPIO_1_tri_i_13(13),
      T => GPIO_1_tri_t_13(13)
    );
GPIO_1_tri_iobuf_14: component IOBUF
     port map (
      I => GPIO_1_tri_o_14(14),
      IO => GPIO_1_tri_io(14),
      O => GPIO_1_tri_i_14(14),
      T => GPIO_1_tri_t_14(14)
    );
GPIO_1_tri_iobuf_15: component IOBUF
     port map (
      I => GPIO_1_tri_o_15(15),
      IO => GPIO_1_tri_io(15),
      O => GPIO_1_tri_i_15(15),
      T => GPIO_1_tri_t_15(15)
    );
GPIO_1_tri_iobuf_16: component IOBUF
     port map (
      I => GPIO_1_tri_o_16(16),
      IO => GPIO_1_tri_io(16),
      O => GPIO_1_tri_i_16(16),
      T => GPIO_1_tri_t_16(16)
    );
GPIO_1_tri_iobuf_17: component IOBUF
     port map (
      I => GPIO_1_tri_o_17(17),
      IO => GPIO_1_tri_io(17),
      O => GPIO_1_tri_i_17(17),
      T => GPIO_1_tri_t_17(17)
    );
GPIO_1_tri_iobuf_18: component IOBUF
     port map (
      I => GPIO_1_tri_o_18(18),
      IO => GPIO_1_tri_io(18),
      O => GPIO_1_tri_i_18(18),
      T => GPIO_1_tri_t_18(18)
    );
GPIO_1_tri_iobuf_19: component IOBUF
     port map (
      I => GPIO_1_tri_o_19(19),
      IO => GPIO_1_tri_io(19),
      O => GPIO_1_tri_i_19(19),
      T => GPIO_1_tri_t_19(19)
    );
GPIO_1_tri_iobuf_2: component IOBUF
     port map (
      I => GPIO_1_tri_o_2(2),
      IO => GPIO_1_tri_io(2),
      O => GPIO_1_tri_i_2(2),
      T => GPIO_1_tri_t_2(2)
    );
GPIO_1_tri_iobuf_20: component IOBUF
     port map (
      I => GPIO_1_tri_o_20(20),
      IO => GPIO_1_tri_io(20),
      O => GPIO_1_tri_i_20(20),
      T => GPIO_1_tri_t_20(20)
    );
GPIO_1_tri_iobuf_21: component IOBUF
     port map (
      I => GPIO_1_tri_o_21(21),
      IO => GPIO_1_tri_io(21),
      O => GPIO_1_tri_i_21(21),
      T => GPIO_1_tri_t_21(21)
    );
GPIO_1_tri_iobuf_22: component IOBUF
     port map (
      I => GPIO_1_tri_o_22(22),
      IO => GPIO_1_tri_io(22),
      O => GPIO_1_tri_i_22(22),
      T => GPIO_1_tri_t_22(22)
    );
GPIO_1_tri_iobuf_23: component IOBUF
     port map (
      I => GPIO_1_tri_o_23(23),
      IO => GPIO_1_tri_io(23),
      O => GPIO_1_tri_i_23(23),
      T => GPIO_1_tri_t_23(23)
    );
GPIO_1_tri_iobuf_3: component IOBUF
     port map (
      I => GPIO_1_tri_o_3(3),
      IO => GPIO_1_tri_io(3),
      O => GPIO_1_tri_i_3(3),
      T => GPIO_1_tri_t_3(3)
    );
GPIO_1_tri_iobuf_4: component IOBUF
     port map (
      I => GPIO_1_tri_o_4(4),
      IO => GPIO_1_tri_io(4),
      O => GPIO_1_tri_i_4(4),
      T => GPIO_1_tri_t_4(4)
    );
GPIO_1_tri_iobuf_5: component IOBUF
     port map (
      I => GPIO_1_tri_o_5(5),
      IO => GPIO_1_tri_io(5),
      O => GPIO_1_tri_i_5(5),
      T => GPIO_1_tri_t_5(5)
    );
GPIO_1_tri_iobuf_6: component IOBUF
     port map (
      I => GPIO_1_tri_o_6(6),
      IO => GPIO_1_tri_io(6),
      O => GPIO_1_tri_i_6(6),
      T => GPIO_1_tri_t_6(6)
    );
GPIO_1_tri_iobuf_7: component IOBUF
     port map (
      I => GPIO_1_tri_o_7(7),
      IO => GPIO_1_tri_io(7),
      O => GPIO_1_tri_i_7(7),
      T => GPIO_1_tri_t_7(7)
    );
GPIO_1_tri_iobuf_8: component IOBUF
     port map (
      I => GPIO_1_tri_o_8(8),
      IO => GPIO_1_tri_io(8),
      O => GPIO_1_tri_i_8(8),
      T => GPIO_1_tri_t_8(8)
    );
GPIO_1_tri_iobuf_9: component IOBUF
     port map (
      I => GPIO_1_tri_o_9(9),
      IO => GPIO_1_tri_io(9),
      O => GPIO_1_tri_i_9(9),
      T => GPIO_1_tri_t_9(9)
    );
zsys_i: component zsys
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(1 downto 0) => DDR_dm(1 downto 0),
      DDR_dq(15 downto 0) => DDR_dq(15 downto 0),
      DDR_dqs_n(1 downto 0) => DDR_dqs_n(1 downto 0),
      DDR_dqs_p(1 downto 0) => DDR_dqs_p(1 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(31 downto 0) => FIXED_IO_mio(31 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      GPIO_1_tri_i(23) => GPIO_1_tri_i_23(23),
      GPIO_1_tri_i(22) => GPIO_1_tri_i_22(22),
      GPIO_1_tri_i(21) => GPIO_1_tri_i_21(21),
      GPIO_1_tri_i(20) => GPIO_1_tri_i_20(20),
      GPIO_1_tri_i(19) => GPIO_1_tri_i_19(19),
      GPIO_1_tri_i(18) => GPIO_1_tri_i_18(18),
      GPIO_1_tri_i(17) => GPIO_1_tri_i_17(17),
      GPIO_1_tri_i(16) => GPIO_1_tri_i_16(16),
      GPIO_1_tri_i(15) => GPIO_1_tri_i_15(15),
      GPIO_1_tri_i(14) => GPIO_1_tri_i_14(14),
      GPIO_1_tri_i(13) => GPIO_1_tri_i_13(13),
      GPIO_1_tri_i(12) => GPIO_1_tri_i_12(12),
      GPIO_1_tri_i(11) => GPIO_1_tri_i_11(11),
      GPIO_1_tri_i(10) => GPIO_1_tri_i_10(10),
      GPIO_1_tri_i(9) => GPIO_1_tri_i_9(9),
      GPIO_1_tri_i(8) => GPIO_1_tri_i_8(8),
      GPIO_1_tri_i(7) => GPIO_1_tri_i_7(7),
      GPIO_1_tri_i(6) => GPIO_1_tri_i_6(6),
      GPIO_1_tri_i(5) => GPIO_1_tri_i_5(5),
      GPIO_1_tri_i(4) => GPIO_1_tri_i_4(4),
      GPIO_1_tri_i(3) => GPIO_1_tri_i_3(3),
      GPIO_1_tri_i(2) => GPIO_1_tri_i_2(2),
      GPIO_1_tri_i(1) => GPIO_1_tri_i_1(1),
      GPIO_1_tri_i(0) => GPIO_1_tri_i_0(0),
      GPIO_1_tri_o(23) => GPIO_1_tri_o_23(23),
      GPIO_1_tri_o(22) => GPIO_1_tri_o_22(22),
      GPIO_1_tri_o(21) => GPIO_1_tri_o_21(21),
      GPIO_1_tri_o(20) => GPIO_1_tri_o_20(20),
      GPIO_1_tri_o(19) => GPIO_1_tri_o_19(19),
      GPIO_1_tri_o(18) => GPIO_1_tri_o_18(18),
      GPIO_1_tri_o(17) => GPIO_1_tri_o_17(17),
      GPIO_1_tri_o(16) => GPIO_1_tri_o_16(16),
      GPIO_1_tri_o(15) => GPIO_1_tri_o_15(15),
      GPIO_1_tri_o(14) => GPIO_1_tri_o_14(14),
      GPIO_1_tri_o(13) => GPIO_1_tri_o_13(13),
      GPIO_1_tri_o(12) => GPIO_1_tri_o_12(12),
      GPIO_1_tri_o(11) => GPIO_1_tri_o_11(11),
      GPIO_1_tri_o(10) => GPIO_1_tri_o_10(10),
      GPIO_1_tri_o(9) => GPIO_1_tri_o_9(9),
      GPIO_1_tri_o(8) => GPIO_1_tri_o_8(8),
      GPIO_1_tri_o(7) => GPIO_1_tri_o_7(7),
      GPIO_1_tri_o(6) => GPIO_1_tri_o_6(6),
      GPIO_1_tri_o(5) => GPIO_1_tri_o_5(5),
      GPIO_1_tri_o(4) => GPIO_1_tri_o_4(4),
      GPIO_1_tri_o(3) => GPIO_1_tri_o_3(3),
      GPIO_1_tri_o(2) => GPIO_1_tri_o_2(2),
      GPIO_1_tri_o(1) => GPIO_1_tri_o_1(1),
      GPIO_1_tri_o(0) => GPIO_1_tri_o_0(0),
      GPIO_1_tri_t(23) => GPIO_1_tri_t_23(23),
      GPIO_1_tri_t(22) => GPIO_1_tri_t_22(22),
      GPIO_1_tri_t(21) => GPIO_1_tri_t_21(21),
      GPIO_1_tri_t(20) => GPIO_1_tri_t_20(20),
      GPIO_1_tri_t(19) => GPIO_1_tri_t_19(19),
      GPIO_1_tri_t(18) => GPIO_1_tri_t_18(18),
      GPIO_1_tri_t(17) => GPIO_1_tri_t_17(17),
      GPIO_1_tri_t(16) => GPIO_1_tri_t_16(16),
      GPIO_1_tri_t(15) => GPIO_1_tri_t_15(15),
      GPIO_1_tri_t(14) => GPIO_1_tri_t_14(14),
      GPIO_1_tri_t(13) => GPIO_1_tri_t_13(13),
      GPIO_1_tri_t(12) => GPIO_1_tri_t_12(12),
      GPIO_1_tri_t(11) => GPIO_1_tri_t_11(11),
      GPIO_1_tri_t(10) => GPIO_1_tri_t_10(10),
      GPIO_1_tri_t(9) => GPIO_1_tri_t_9(9),
      GPIO_1_tri_t(8) => GPIO_1_tri_t_8(8),
      GPIO_1_tri_t(7) => GPIO_1_tri_t_7(7),
      GPIO_1_tri_t(6) => GPIO_1_tri_t_6(6),
      GPIO_1_tri_t(5) => GPIO_1_tri_t_5(5),
      GPIO_1_tri_t(4) => GPIO_1_tri_t_4(4),
      GPIO_1_tri_t(3) => GPIO_1_tri_t_3(3),
      GPIO_1_tri_t(2) => GPIO_1_tri_t_2(2),
      GPIO_1_tri_t(1) => GPIO_1_tri_t_1(1),
      GPIO_1_tri_t(0) => GPIO_1_tri_t_0(0),
      PWM_L => PWM_L,
      PWM_R => PWM_R,
      Vp_Vn_v_n => Vp_Vn_v_n,
      Vp_Vn_v_p => Vp_Vn_v_p,
      csi_c_clk_n => csi_c_clk_n,
      csi_c_clk_p => csi_c_clk_p,
      csi_d_lp_n(0) => csi_d_lp_n(0),
      csi_d_lp_p(0) => csi_d_lp_p(0),
      csi_d_n(1 downto 0) => csi_d_n(1 downto 0),
      csi_d_p(1 downto 0) => csi_d_p(1 downto 0),
      hdmi_clk_n => hdmi_clk_n,
      hdmi_clk_p => hdmi_clk_p,
      hdmi_data_n(2 downto 0) => hdmi_data_n(2 downto 0),
      hdmi_data_p(2 downto 0) => hdmi_data_p(2 downto 0)
    );
end STRUCTURE;
