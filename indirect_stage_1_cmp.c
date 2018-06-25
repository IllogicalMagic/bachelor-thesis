find_iv_cmp(iv_desc) {
  // Следующее значение индуктивной переменной
  // должно быть в выходе из цикла.
  if (iv_desc.incr not in loop_exiting_block)
    return false;

  brn = loop_exiting_block.get_terminator();
  if (brn is unconditional)
    return false;

  // Сравнение для индуктивной переменной --
  // это условие выхода из цикла.
  cmp = brn.get_condition();

  // Проверка, что следующее значение сравнивается с инвариантом цикла.
  if (cmp.ops not contain loop_invariant)
    return false;
  if (cmp.ops not contain iv_desc.incr)
    return false;

  // Добавление информации о найденном сравнении.
  update_iv_desc_with_cmp(cmp, iv_desc);
  return true;
}
