/*
** list.h for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 24 17:56:45 2016 querat_g
// Last update Thu Jun 16 10:49:07 2016 querat_g
*/

#ifndef LIST_H_
# define LIST_H_

# define LIST_IS_EMPTY(x)   (!x || !x->first || !x->first->data)
# define LIST_FIRST_DATA(x) (!LIST_IS_EMPTY(x) ? x->first->data : (void*)0)
# define LIST_HAS_NODE(x)   (x && x->first)
# define LIST_FIRST_NODE(x) (LIST_HAS_NODE(x) ? x->first : (void*)0)

/*
** Maillon de la liste chaînée
*/
typedef struct  s_node
{
  struct s_node	*next;
  void		*data;
}		t_node;

/*
** Contrôleur de la liste chainée
*/
typedef struct  s_list
{
  t_node        *first;
  t_node        *last;
  int           (*append)(struct s_list **this, void *data);
  int           (*prepend)(struct s_list **this, void *data);
  int           (*insert)(struct s_list **this, int offset, void *data);
  void          (*print)(struct s_list *this, void (*printer)(void*));
  void          (*destruct)(struct s_list **this, void (*destructor)(void*));
  int           (*rm_node)(struct s_list *this, int offset,
                           void (*destructor)(void*));
  int           (*rm_first_node)(struct s_list *this,
                                 void (*destructor)(void*));
  int           (*rm_last_node)(struct s_list *this,
                                void (*destructor)(void*));
  int		(*sort)(struct s_list *this, int (*cmp)(void *p1, void *p2));
  int           (*for_each)(struct s_list *this,
                            int (*function)(void*, void*),
                            void *data);
  int           (*remove_if)(struct s_list *this, int (*if_function)(void*),
                                    void (*rm_function)(void*));
  int           (*count_if)(struct s_list *this, int (*if_function)(void*));
}               t_list;

t_list  *new_list(void);
int     list_append(t_list **this, void *data);
int     list_prepend(t_list **this, void *data);
int     list_insert(t_list **this, int offset, void *data);
int     list_rm_first_node(t_list *this,
                                   void (*destructor)(void*));
int     list_rm_last_node(t_list *this,
                                  void (*destructor)(void*));
int     list_rm_node(t_list *this, int offset,
                     void (*destructor)(void*));
int     list_len(t_list *this);
void    list_print(t_list *this, void (*printer)(void*));
void    list_destruct(t_list **this, void (*destructor)(void*));
int	list_sort(t_list *list, int (*cmp)(void *p1, void *p2));
int     list_for_each(t_list *this, int (*function)(void*, void*), void *data);
int     list_remove_if(t_list *this, int (*if_function)(void*),
                       void (*rm_function)(void*));
int     list_count_if(t_list *this, int (*if_function)(void*));

#endif /* !list.h */
