#!/bin/bash

set -eu

cd `dirname $0`

python cpp/docs/documents.py
python cpp/docs/title.py        > docs/cpp/index.md
python ocaml/docs/documents.py
python ocaml/docs/title.py      > docs/ocaml/index.md
