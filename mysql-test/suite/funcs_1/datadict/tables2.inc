# suite/funcs_1/datadict/tables2.inc
#
# Auxiliary script to be sourced by suite/funcs_1/datadict/tables1.inc.
#
# Author:
# 2008-01-23 mleich WL#4203 Reorganize and fix the data dictionary tests of
#                           testsuite funcs_1
#                   Create this script based on older scripts and new code.
#
################################################################################

#  8 TABLE_ROWS
#  9 AVG_ROW_LENGTH
# 10 DATA_LENGTH
# 11 MAX_DATA_LENGTH
# 12 INDEX_LENGTH
# 13 DATA_FREE
# 15 CREATE_TIME
# 16 UPDATE_TIME
# 17 CHECK_TIME
# 20 CREATE_OPTIONS
# 21 TABLE_COMMENT   User defined comment
#                    + InnoDB
#                    + InnoDB: "InnoDB free: <number_kB> kB" appended
#                      <number_kB> depends on tablespace history!
#                    The LEFT/INSTR/IF/LENGTH stuff should remove these
#                    storage engine specific part.
let $innodb_pattern = 'InnoDB free';
--vertical_results
# We do not unify the engine name here, because the rowformat is
# specific to the engine.
--replace_result Dynamic DYNAMIC_OR_PAGE Page DYNAMIC_OR_PAGE MyISAM MYISAM_OR_MARIA Aria MYISAM_OR_MARIA
--replace_column  8 "#TBLR#" 9 "#ARL#" 10 "#DL#" 11 "#MDL#" 12 "#IL#" 13 "#DF#" 15 "#CRT#" 16 "#UT#" 17 "#CT#" 20 "#CO#" 21 "#TC#"
eval
SELECT *,
       LEFT( table_comment,
             IF(INSTR(table_comment,$innodb_pattern) = 0,
                LENGTH(table_comment),
                INSTR(table_comment,$innodb_pattern) - 1))
       AS "user_comment",
       '-----------------------------------------------------' AS "Separator"
FROM information_schema.tables
$my_where
ORDER BY table_schema,table_name;
--horizontal_results
