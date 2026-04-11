/* DB_impl.h
 *
 * This file contains private helper function declarations
 * used by the database implementation.
 *
 * Authors: Almoatassem Namroush, Aiob Ali, Kunwar Mahajan
 * Lab instructor: Ardy
 */

#ifndef DB_IMPL_H
#define DB_IMPL_H

int findValue(Table *table, int size, char *value);
int addValue(Table **table, int *size, char *value);

#endif