/**
 * Copyright (C) 2023 Devin Rockwell
 *
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with walnut. If not, see <http://www.gnu.org/licenses/>.
 */

#include <check.h>
#include <walnut/debug.h>
#include <walnut/walnut.h>

START_TEST(test_ldi)
{
  Walnut walnut;
  uint64_t code[] = {
    0x100000000040000,
  };
  walnutInit(&walnut, code, 1);
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_lda)
{
  Walnut walnut;
  uint64_t code[] = {
    0x200010000000000,
    0,
    0xA,
  };
  walnutInit(&walnut, code, 3);
  walnut.registers[1] = 2;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 0xA);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_ldr)
{
  Walnut walnut;
  uint64_t code[] = {
    0x301000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 4;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[1], 4);
  walnutFree(&walnut);
}
END_TEST

Suite *
load_suite()
{
  Suite *s       = suite_create("Loads");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_ldi);
  tcase_add_test(tc_core, test_lda);
  tcase_add_test(tc_core, test_ldr);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_sto)
{
  Walnut walnut;
  uint64_t code[] = {
    0x400010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[1] = 10;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.mem.data[1], 10);
  walnutFree(&walnut);
}
END_TEST

Suite *
store_suit()
{
  Suite *s       = suite_create("Stores");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sto);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_add)
{
  Walnut walnut;
  uint64_t code[] = {
    0x502000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 15);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_sub)
{
  Walnut walnut;
  uint64_t code[] = {
    0x602000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 5);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_mul)
{
  Walnut walnut;
  uint64_t code[] = {
    0x702000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 50);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_div)
{
  Walnut walnut;
  uint64_t code[] = {
    0x802000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_mod)
{
  Walnut walnut;
  uint64_t code[] = {
    0x902000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 4;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 2);
  walnutFree(&walnut);
}
END_TEST

Suite *
math_suite()
{
  Suite *s       = suite_create("Math");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add);
  tcase_add_test(tc_core, test_sub);
  tcase_add_test(tc_core, test_mul);
  tcase_add_test(tc_core, test_div);
  tcase_add_test(tc_core, test_mod);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_lbs)
{
  Walnut walnut;
  uint64_t code[] = {
    0xA00000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 2;
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_rbs)
{
  Walnut walnut;
  uint64_t code[] = {
    0xB00000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 2;
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 1);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_and)
{
  Walnut walnut;
  uint64_t code[] = {
    0xC00000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 1);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_bor)
{
  Walnut walnut;
  uint64_t code[] = {
    0xD02000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[2], 3);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_xor)
{
  Walnut walnut;
  uint64_t code[] = {
    0xE00000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_not)
{
  Walnut walnut;
  uint64_t code[] = {
    0xF00000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], ~3);
  walnutFree(&walnut);
}
END_TEST

Suite *
bitwise_suite()
{
  Suite *s       = suite_create("Bitwise");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_lbs);
  tcase_add_test(tc_core, test_rbs);
  tcase_add_test(tc_core, test_and);
  tcase_add_test(tc_core, test_bor);
  tcase_add_test(tc_core, test_xor);
  tcase_add_test(tc_core, test_not);
  return s;
}

START_TEST(test_jmp)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1000000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jeq_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1100000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_EQUAL;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jeq_not_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1100000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jne_not_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1200000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jne_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1200000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_EQUAL;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jgt_greater)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1300000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_GREATER;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jgt_not_greater)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1300000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jlt_less)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1400000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jlt_not_less)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1400000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_GREATER;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jge_greater)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1500000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_GREATER;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jge_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1500000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_EQUAL;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jge_false)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1500000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jle_less)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1600000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_LESS;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jle_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1600000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_EQUAL;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_jle_false)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1600000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.flags        = WALNUT_FLAG_GREATER;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 2);
  walnutFree(&walnut);
}
END_TEST

Suite *
jump_suite()
{
  Suite *s       = suite_create("Jumps");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_jmp);
  tcase_add_test(tc_core, test_jeq_equal);
  tcase_add_test(tc_core, test_jeq_not_equal);
  tcase_add_test(tc_core, test_jne_not_equal);
  tcase_add_test(tc_core, test_jne_equal);
  tcase_add_test(tc_core, test_jgt_greater);
  tcase_add_test(tc_core, test_jgt_not_greater);
  tcase_add_test(tc_core, test_jlt_less);
  tcase_add_test(tc_core, test_jlt_not_less);
  tcase_add_test(tc_core, test_jge_greater);
  tcase_add_test(tc_core, test_jge_equal);
  tcase_add_test(tc_core, test_jge_false);
  tcase_add_test(tc_core, test_jle_less);
  tcase_add_test(tc_core, test_jle_equal);
  tcase_add_test(tc_core, test_jle_false);
  return s;
}

START_TEST(test_cmp_equal)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1700010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 3;
  walnut.registers[1] = 3;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.flags, WALNUT_FLAG_EQUAL);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_cmp_greater)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1700010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 4;
  walnut.registers[1] = 3;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.flags, WALNUT_FLAG_GREATER);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_cmp_less)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1700010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 2;
  walnut.registers[1] = 3;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.flags, WALNUT_FLAG_LESS);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_brk_increase)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1800010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 128);
  ck_assert_uint_eq(walnut.mem.len, 134);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_brk_decrease)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1800010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[1] = -5;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 128);
  ck_assert_uint_eq(walnut.mem.len, 124);
  walnutFree(&walnut);
}
END_TEST

Suite *
misc_suite()
{
  Suite *s       = suite_create("Misc");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_cmp_equal);
  tcase_add_test(tc_core, test_cmp_greater);
  tcase_add_test(tc_core, test_cmp_less);
  tcase_add_test(tc_core, test_brk_increase);
  tcase_add_test(tc_core, test_brk_decrease);
  return s;
}

START_TEST(test_walnutMemInit)
{
  WalnutMem mem;
  walnutMemInit(&mem, 1024 / 8 + 1, 1);
  ck_assert_ptr_nonnull(mem.data);
  ck_assert_uint_eq(mem.len, 1024 / 8 + 1);
  ck_assert_uint_eq(mem.codeLen, 1);
  mem.data[1024] = 4;
  ck_assert_uint_eq(mem.data[1024], 4);
  walnutMemFree(&mem);
}
END_TEST

START_TEST(test_walnutMemInit_len_less_than_codeLen)
{
  WalnutMem mem;
  walnutMemInit(&mem, 1, 3);
  walnutMemFree(&mem);
}
END_TEST

START_TEST(test_walnutMemBrk_increase)
{
  WalnutMem mem;
  walnutMemInit(&mem, 0, 0);
  uint64_t top = walnutMemBrk(&mem, 5);
  ck_assert_ptr_nonnull(mem.data);
  ck_assert_uint_eq(mem.len, 5);
  mem.data[4] = 4;
  ck_assert_uint_eq(mem.data[4], 4);
  walnutMemFree(&mem);
}
END_TEST

START_TEST(test_walnutMemBrk_decrease)
{
  WalnutMem mem;
  walnutMemInit(&mem, 5, 0);
  uint64_t top = walnutMemBrk(&mem, -2);
  ck_assert_ptr_nonnull(mem.data);
  ck_assert_uint_eq(mem.len, 3);
  ck_assert_uint_eq(top, 4);
  mem.data[2] = 4;
  ck_assert_uint_eq(mem.data[2], 4);
  walnutMemFree(&mem);
}
END_TEST

START_TEST(test_walnutMemBrk_resize_smaller_than_text_segment)
{
  WalnutMem mem;
  walnutMemInit(&mem, 5, 4);
  uint64_t top = walnutMemBrk(&mem, -2);
  walnutMemFree(&mem);
}
END_TEST

Suite *
WalnutMem_suite()
{
  Suite *s       = suite_create("WalnutMem");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_walnutMemInit);
  tcase_add_exit_test(tc_core, test_walnutMemInit_len_less_than_codeLen,
                      EXIT_FAILURE);
  tcase_add_test(tc_core, test_walnutMemBrk_increase);
  tcase_add_test(tc_core, test_walnutMemBrk_decrease);
  tcase_add_exit_test(tc_core,
                      test_walnutMemBrk_resize_smaller_than_text_segment,
                      EXIT_FAILURE);
  return s;
}

START_TEST(test_iwp)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1900000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.wp, 1);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_dwp)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1A00000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.wp = 2;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.wp, 1);
  walnutFree(&walnut);
}
END_TEST

Suite *
register_window_suite()
{
  Suite *s       = suite_create("Register Windows");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_iwp);
  tcase_add_test(tc_core, test_dwp);
  return s;
}

START_TEST(test_jsr)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1B00000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[16] = 100;
  walnut.wp++;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 101);
  ck_assert_uint_eq(walnut.registers[15], 1);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_ret)
{
  Walnut walnut;
  uint64_t code[] = {
    0x1C00000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[15] = 100;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.pc, 101);
  walnutFree(&walnut);
}
END_TEST

Suite *
subroutine_suite()
{
  Suite *s       = suite_create("Subroutine");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_jsr);
  tcase_add_test(tc_core, test_ret);
  return s;
}

int
main()
{
  int numberFailed;
  Suite *ld     = load_suite();
  Suite *st     = store_suit();
  Suite *m      = math_suite();
  Suite *b      = bitwise_suite();
  Suite *j      = jump_suite();
  Suite *mi     = misc_suite();
  Suite *wm     = WalnutMem_suite();
  Suite *w      = register_window_suite();
  Suite *s      = subroutine_suite();
  SRunner *ldSr = srunner_create(ld);
  SRunner *stSr = srunner_create(st);
  SRunner *mSr  = srunner_create(m);
  SRunner *bSr  = srunner_create(b);
  SRunner *jSr  = srunner_create(j);
  SRunner *miSr = srunner_create(mi);
  SRunner *wmSr = srunner_create(wm);
  SRunner *wSr  = srunner_create(w);
  SRunner *sSr  = srunner_create(s);

  srunner_run_all(ldSr, CK_NORMAL);
  numberFailed = srunner_ntests_failed(ldSr);

  srunner_run_all(stSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(stSr);

  srunner_run_all(mSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(mSr);

  srunner_run_all(bSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(bSr);

  srunner_run_all(jSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(jSr);

  srunner_run_all(miSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(miSr);

  srunner_run_all(wmSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(wmSr);

  srunner_run_all(wSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(wSr);

  srunner_run_all(sSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(sSr);

  srunner_free(ldSr);
  srunner_free(stSr);
  srunner_free(mSr);
  srunner_free(bSr);
  srunner_free(jSr);
  srunner_free(miSr);
  srunner_free(wSr);
  srunner_free(sSr);
  return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}