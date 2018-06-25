// Оценка итераций для предподкачки.
sz = estimate_loop_size();
iters_ahead = distance / sz;

prefetched_inst = {};
for (inst in loop) {
  if (inst is load)
    addr = inst.get_addr();
  else if (inst is store && prefetch_stores)
    addr = inst.get_addr();
  else continue;

  no_pref = false;
  for (pref in prefetched_inst)
    // Не вставлять лишние предподкачки.
    if (abs(pref.addr - inst.addr) < cache_line) {
      no_pref = true;
      break;
    }
  if (no_pref)
    continue;

  // Не для всех инструкций или адресов возможна предподкачка.
  if (!is_fit_for_prefetch(inst) && is_dependent_on_iv(addr))
    continue;

  generate_prefetch(addr, inst.is_load);
  prefetched_inst.add(addr, inst.is_load);
}
