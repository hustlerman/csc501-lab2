/* frame.c - manage physical frames */
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

/*-------------------------------------------------------------------------
 * init_frm - initialize frm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL init_frm()
{
  // Creates the frame table
  for(int i = 0; i < NFRAMES; i++) {
    frm_tab[i].fr_status = FRM_UNMAPPED;
    frm_tab[i].fr_refcnt = 0;
  }
  
  // Creates the free list of frames
  free_frs = getmem(sizeof(ffr_node_t));
  ffr_node_t *curr = free_frs;
  for(int i = 0; i < NFRAMES; i++) {
    curr->fr_index = i;
    curr->next = getmem(sizeof(ffr_node_t));
    curr = curr->next;
  }
  curr->next = NULL;

  return OK;
}

/*-------------------------------------------------------------------------
 * get_frm - get a free frame according page replacement policy
 *-------------------------------------------------------------------------
 */
SYSCALL get_frm(int* avail)
{
  // Check free list of frames first
  if(free_frs != NULL) {
    ffr_node_t *temp = free_frs;
    int fr_index = free_frs->fr_index;
    free_frs = free_frs->next;
    freemem(temp, sizeof(ffr_node_t));
  }

  kprintf("To be implemented!\n");
  return OK;
}

/*-------------------------------------------------------------------------
 * free_frm - free a frame 
 *-------------------------------------------------------------------------
 */
SYSCALL free_frm(int i)
{
  frm_tab[i].fr_status = FRM_UNMAPPED;
  return OK;
}



