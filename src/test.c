#include "./parser.h"
#include "./transformations.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(create_data_1) {
  data_t *data = NULL;
  ck_assert_int_eq(create_data(data), 1);
  ck_assert_ptr_nonnull(data);
  free(data);
}
END_TEST

START_TEST(parsline_1) {
  char *filename = "data_null_test";
  data_t *data = NULL;
  ck_assert_int_eq(parsline(filename, data), 0);
}
END_TEST

START_TEST(parsline_2) {
  char *filename = "file_not_found";
  data_t *data = NULL;
  create_data(data);
  ck_assert_int_eq(parsline(filename, data), 0);
  ck_assert_ptr_nonnull(data);
  free(data);
}
END_TEST

START_TEST(init_data_1) {
  data_t *data = NULL;
  ck_assert_int_eq(init_data(data), 0);
}
END_TEST

START_TEST(init_data_2) {
  data_t *data;
  int v, f;
  v = 4;
  f = 4;

  create_data(data);
  data->count_of_facets = 4;
  data->count_of_vertexes = 4;
  init_data(data);

  ck_assert_ptr_nonnull(data->matrix_3d.matrix);
  for (int i = 0; i < data->matrix_3d.rows; ++i)
    ck_assert_ptr_nonnull(data->matrix_3d.matrix[i]);
  ck_assert_ptr_nonnull(data->polygons);
  free(data->matrix_3d.matrix);
  for (int i = 0; i < data->matrix_3d.rows; ++i)
    free(data->matrix_3d.matrix[i]);
  free(data->polygons);

}
END_TEST

START_TEST(init_polygon_1) {
  data_t *data = NULL;
  ck_assert_int_eq(init_polygon(data, "data_null_test", 0), 0);
}
END_TEST

START_TEST(init_polygon_2) {
  data_t *data = malloc(sizeof(data_t *));
  ck_assert_int_eq(init_polygon(data, NULL, 0), 0);
  free(data);
}
END_TEST

START_TEST(init_polygon_3) {
  data_t *data;
  int f, v, index;
  char *line;

  v = 4;
  f = 4;
  index = 1;
  line = "1 2 3";

  create_data(data);
  data->count_of_facets = 4;
  data->count_of_vertexes = 4;

  init_data(data);
  init_polygon(data, line, index);

  ck_assert_ptr_nonnull(data->polygons[index].vertexes);
  for (int i = 0; i < data->polygons[index].numbers_of_vertexes_in_facets; ++i)
    ck_assert_int_eq(data->polygons[index].vertexes[i], i + 1);

  free(data->polygons[index].vertexes);
  free(data->polygons);
  free(data->matrix_3d.matrix);
  free(data);
}
END_TEST

Suite *s21_3d() {
  Suite *suite;

  suite = suite_create("s21_3d");
  TCase *tcase_create_data = suite_create("create_data");
  TCase *tcase_parsline = suite_create("parline");
  TCase *tcase_init_data = suite_create("init_data");
  TCase *tcase_init_polygon = suite_create("init_polygon");
  TCase *tcase_destroy_data = suite_create("destroy_data");

  suite_add_tcase(suite, tcase_create_data);
  tcase_add_test(tcase_create_data, create_data_1);

  suite_add_tcase(suite, tcase_parsline);
  tcase_add_test(tcase_parsline, parsline_1);
  tcase_add_test(tcase_parsline, parsline_2);

  suite_add_tcase(suite, tcase_init_data);
  tcase_add_test(tcase_init_data, init_data_1);
  tcase_add_test(tcase_init_data, init_data_2);

  suite_add_tcase(suite, tcase_init_polygon);
  tcase_add_test(tcase_init_polygon, init_polygon_1);
  tcase_add_test(tcase_init_polygon, init_polygon_2);
  tcase_add_test(tcase_init_polygon, init_polygon_3);

  return suite;
}

int main() {
  Suite *suite = s21_3d();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  srunner_free(suite);
  return 0;
}