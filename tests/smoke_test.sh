#!/bin/bash
# Basic smoke test for Hotel Keycard System
# Runs the binary with automated input and checks for expected output

BINARY="./build/HotelKeycard"
PASS=0
FAIL=0

assert_contains() {
    local desc="$1"
    local output="$2"
    local expected="$3"
    if echo "$output" | grep -q "$expected"; then
        echo "  ✅  PASS: $desc"
        ((PASS++))
    else
        echo "  ❌  FAIL: $desc (expected: '$expected')"
        ((FAIL++))
    fi
}

echo "═══════════════════════════════════════"
echo "  Hotel Keycard System – Smoke Tests"
echo "═══════════════════════════════════════"

# Test 1: Generate a keycard
echo "▶ Test 1: Generate keycard for 'Alice'"
OUTPUT=$(echo -e "1\nAlice\n7" | $BINARY 2>/dev/null)
assert_contains "Keycard issued for Alice" "$OUTPUT" "KEYCARD ISSUED"
assert_contains "Key saved to database"    "$OUTPUT" "saved"

# Test 2: Validate a bad key
echo "▶ Test 2: Validate non-existent key"
OUTPUT=$(echo -e "2\n00000000\n7" | $BINARY 2>/dev/null)
assert_contains "Access denied for unknown key" "$OUTPUT" "Denied"

# Test 3: Auto-expire (no old keys, should report none)
echo "▶ Test 3: Auto-expire with fresh keys"
OUTPUT=$(echo -e "5\n7" | $BINARY 2>/dev/null)
assert_contains "Expire scan runs without crash" "$OUTPUT" "keycard"

echo ""
echo "═══════════════════════════════════════"
echo "  Results: $PASS passed, $FAIL failed"
echo "═══════════════════════════════════════"

# Cleanup
rm -f data/keycards.txt

exit $FAIL
