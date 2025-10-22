#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
MINICOMPILER="$REPO_ROOT/minicompiler"
TEST_DIR="$REPO_ROOT/tests"

if [[ ! -x "$MINICOMPILER" ]]; then
  echo "error: build minicompiler before running tests" >&2
  exit 1
fi

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

pass_count=0
fail_count=0

printf "Running tests...\n\n"

while IFS= read -r -d '' input; do
  base=$(basename "${input%.cm}")
  expected="$TEST_DIR/$base.expected"
  if [[ ! -f "$expected" ]]; then
    echo "[SKIP] $base (missing expected output)"
    continue
  fi

  asm="$tmpdir/$base.s"
  actual="$tmpdir/$base.out"

  if ! "$MINICOMPILER" "$input" "$asm" >/dev/null; then
    echo "[FAIL] $base (compilation error)"
    fail_count=$((fail_count + 1))
    continue
  fi

  if ! spim -file "$asm" >"$actual.raw" 2>"$actual.err"; then
    echo "[FAIL] $base (spim execution error)"
    fail_count=$((fail_count + 1))
    continue
  fi

  grep -v '^Loaded:' "$actual.raw" | sed '/^$/d' >"$actual"

  if diff -u "$expected" "$actual" >"$actual.diff"; then
    echo "[PASS] $base"
    pass_count=$((pass_count + 1))
  else
    echo "[FAIL] $base"
    fail_count=$((fail_count + 1))
    echo "  expected:"
    sed 's/^/    /' "$expected"
    echo "  actual:"
    sed 's/^/    /' "$actual"
    echo "  diff:"
    sed 's/^/    /' "$actual.diff"
  fi
done < <(find "$TEST_DIR" -maxdepth 1 -name '*.cm' -print0 | sort -z)

printf "\nSummary: %d passed, %d failed\n" "$pass_count" "$fail_count"

exit $((fail_count == 0 ? 0 : 1))
