prealloc() {
  store_addrs = {}
  store_size = 0
  for (insn in loop) {
    // В цикле не должно быть чтений.
    if (insn is load)
      return;
    if (insn is store) {
      // Все записи в память должны быть одинакового размера.
      if (store_size == 0)
        store_size = store.value_size;
      else if (store.value_size != store_size)
        return;
      store_addrs.add(store.addr);
    }
  }

  // Индуктивная переменная должна изменяться так,
  // чтобы на каждой итерации заполнялась новая кэш-линия.
  if (IV.step * store_size != cache_line_size)
    return;

  // Все адреса должны находиться в пределах кэш-линии.
  for (addr1 in store_addrs) {
    for (addr2 in store_addrs) {
      if (abs(addr2 - addr1) >= cache_line_size)
        return;
    }
  }

  // Самый младший адрес должен быть выровнен по границе кэш-линии.
  base = find_base_addr(store_addrs);
  if (alignof(base) != cache_line_size)
    return;

  // Адреса должны полностью покрывать кэш-линию.
  if (!is_line_covered(store_addrs, store_size, cache_line_size))
    return;

  generate_prealloc(base);
}
