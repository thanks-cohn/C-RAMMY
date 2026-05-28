#!/usr/bin/env bash
set -euo pipefail

mkdir -p logs

echo "[SMOKE] building C-RAMMY"
make all

echo "[SMOKE] starting rammyctl listener"
timeout 8s ./rammyctl > logs/smoke_rammyctl.log 2>&1 &
CTL_PID=$!

sleep 1

echo "[SMOKE] starting rammyd heartbeat daemon"
RAMMY_BCAST=127.0.0.1 timeout 5s ./rammyd > logs/smoke_rammyd.log 2>&1 || true

CTL_STATUS=0
wait "$CTL_PID" || CTL_STATUS=$?

if [ "$CTL_STATUS" -ne 0 ] && [ "$CTL_STATUS" -ne 124 ]; then
    echo "[SMOKE] rammyctl failed with status $CTL_STATUS"
    exit 1
fi

echo "[SMOKE] checking daemon log"
grep -q "C-RAMMY v0 NODE ONLINE" logs/smoke_rammyd.log
grep -q "RAMMY HEARTBEAT" logs/smoke_rammyd.log

echo "[SMOKE] checking listener log"
grep -q "FABRIC LISTENER ONLINE" logs/smoke_rammyctl.log
grep -q "pooled_total_ram" logs/smoke_rammyctl.log

echo "[SMOKE] PASS"
echo "[SMOKE] logs:"
echo "  logs/smoke_rammyd.log"
echo "  logs/smoke_rammyctl.log"
