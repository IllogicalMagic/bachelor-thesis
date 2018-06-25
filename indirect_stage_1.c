is_iv(phi, iv_desc) {
  // Индуктивная переменная берётся
  // только для простых случаев.
  if (phi.num_operands != 2)
    return false;

  // Один из операндов -- стартовое значение.
  if (phi.ops not contain loop_invariant)
    return false;

  start = get_start_value(phi);
  // Второй операнд -- значение на следующей итерации.
  incr = get_increment(phi);
  if (!is_allowed_iv_operation(incr))
    return false;

  // Приращение должно быть инвариантом цикла.
  if (incr.ops not contain loop_invariant)
    return false;

  // Один из операндов -- этот же узел.
  if (incr.ops not contain phi)
    return false;

  update_iv_desc(phi, iv_desc);
  return true;
}
