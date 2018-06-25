preheader = get_loop_preheader();
for (pref in prefetched_inst) {
  // Берётся стартовый адрес индуктивной переменной.
  start = pref.addr.get_start_address();
  // Предподкачка вставляется перед головой цикла.
  generate_prefetch_pos(start, pref.is_load, preheader);
}
