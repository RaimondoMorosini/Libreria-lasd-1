
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& val) {
  Data tmp = Successor(val);
  
  // First remove the original element (val)
  Remove(val);
  
  // Then remove the successor and get the result 
  Remove(tmp);
  
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
  Remove(Successor(val));
}

} // namespace lasd

#endif // SETVEC_TPP