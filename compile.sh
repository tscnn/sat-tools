#!/bin/bash
P=${0%/*}
$P/analyzecnf/compile.sh
$P/coloringcnf/compile.sh
$P/randomcnf/compile.sh
$P/schoening/compile.sh
$P/strongcnf/compile.sh
$P/hypercolcnf/compile.sh
$P/one_cnf/compile.sh
$P/isocnf/compile.sh
$P/hgv_cnf/compile.sh

