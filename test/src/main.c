/**
 * Copyright (C) 2023 Devin Rockwell
 * 
 * This file is part of walnut.
 * 
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with walnut.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <check.h>
#include <walnut/walnut.h>

START_TEST(test_load) {
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

Suite *walnut_suite() {
    Suite *s;
    TCase *tc_core;
    s = suite_create("Walnut");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_load);
    suite_add_tcase(s, tc_core);
    
    return s;
}

int main() {
    int numberFailed;
    Suite *s;
    SRunner *sr;
    
    s = walnut_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numberFailed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}