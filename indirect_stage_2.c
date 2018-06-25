dfg_dfs(inst, chain, ivset) {
  found = false;
  for (op in inst.ops) {
    // op -- индуктивная переменная.
    if (op is in ivset)
      return true;
    // Инварианты цикла не рассматриваются.
    else if (op is loop_invariant)
      return false;
    else
      if (dfg_dfs(inst, chain, ivset)) {
        // Индуктивная переменная найдена,
        // теперь формируется цепочка.
        found = true;
        break;
      }
  }

  // Текущая инструкция добавляется в цепочку.
  if (found)
    chain.push_back(inst);
  return found;
}
