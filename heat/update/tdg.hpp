#include <stddef.h>
#include <atomic>
struct kmp_task_t;
struct kmp_node_info
{
  int static_id;
  struct kmp_task_t *task;
  int * succesors;
  int nsuccessors;
  std::atomic<int> npredecessors_counter;
  int npredecessors;
  int successors_size;
  int static_thread;
  int pragma_id;
  void * private_data;
  void * shared_data;
  void * parent_task;
  struct kmp_node_info * next_waiting_tdg;
  unsigned long exe_time;
};
extern  "C" void __kmpc_set_tdg(struct kmp_node_info *tdg, int gtid, uint32_t tdg_id, int ntasks, int *roots, int nroots);
extern "C" void __kmpc_taskgraph(void *loc_ref, int gtid, uint32_t tdg_id, void (*entry)(void *), void *args, int tdg_type, int if_cond, bool nowait, bool isSingleBasicBlock);
