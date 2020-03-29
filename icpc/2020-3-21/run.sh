# perf stat \
# -r 10 \
# -e cycles,l1d_pend_miss.pending,l1d_pend_miss.pending_cycles,l2_rqsts.all_pf,l2_lines_out.useless_hwpf,l2_rqsts.pf_miss,l2_rqsts.references,mem_inst_retired.all_loads,mem_load_retired.l1_hit,mem_load_retired.l1_miss,mem_load_retired.l2_hit,mem_load_retired.l2_miss,mem_load_retired.l3_hit,mem_load_retired.l3_miss,inst_retired.any \
# -M L1D_Cache_Fill_BW,L2_Cache_Fill_BW,L3_Cache_Access_BW,L3_Cache_Fill_BW \
# ./list2.out 10000000

perf stat \
-r 1 \
-e cycle_activity.cycles_l1d_miss,cycle_activity.cycles_l2_miss,cycle_activity.cycles_mem_any,cycle_activity.stalls_l1d_miss,cycle_activity.stalls_l2_miss,cycle_activity.stalls_mem_any,cycle_activity.stalls_total,mem_trans_retired.load_latency_gt_4,mem_trans_retired.load_latency_gt_8,mem_trans_retired.load_latency_gt_16,mem_trans_retired.load_latency_gt_32 \
./list.out 10000000

#perf record \
#-e cycles,l1d_pend_miss.pending,l1d_pend_miss.pending_cycles,l2_rqsts.all_pf,l2_lines_out.useless_hwpf,l2_rqsts.pf_miss,l2_rqsts.references,mem_inst_retired.all_loads,mem_load_retired.l1_hit,mem_load_retired.l1_miss,mem_load_retired.l2_hit,mem_load_retired.l2_miss,mem_load_retired.l3_hit,mem_load_retired.l3_miss,inst_retired.any \
#-c 1000000 \
#-o list.data \
#./list.out 10000000
