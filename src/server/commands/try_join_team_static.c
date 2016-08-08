/*
** try_join_team_static.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 10:32:37 2016 querat_g
** Last update Sun Jun 26 22:49:23 2016 schmou_a
*/

static t_cli *gui = NULL;

static void pnw_init(void *ptr)
{
    char      g_buff[512];
    t_cli     *c;

    if ((c = ptr) == NULL || gui == NULL || c->is_graphic ||
      !c->team || !c->team->name)
        return;
    snprintf(g_buff, 512, "pnw %d %ld %ld %d %d %s\n",
             c->sock.fd,
             c->x_pos,
             c->y_pos,
             c->direction,
             c->level,
             c->team->name);
    enqueue_msg(gui, g_buff);
}

static void enw_init(void *ptr)
{
    char      g_buff[512];
    t_egg     *egg;

    if ((egg = ptr) == NULL || gui == NULL)
        return;
    snprintf(g_buff, 50, "enw %lu %u %ld %ld\n", egg->id, 0,
             egg->x, egg->y);
    enqueue_msg(gui, g_buff);
}

static int  enw_init_list(void *data, void *useless)
{
    t_team    *team;

    if ((team = data) == NULL || team->eggs == NULL)
        return (true);
    (void)useless;
    ht_foreach(team->eggs, enw_init);
    return (true);
}

static void try_join_team_egg(t_team *curteam, t_cli *c)
{
    t_egg     *egg;

    if (list_len(curteam->eggs_sorted) &&
        (egg = curteam->eggs_sorted->first->data))
    {
        c->x_pos = egg->x;
        c->y_pos = egg->y;
        ebo(c);
        eht(c);
        ht_rm_entry(curteam->eggs, &(egg->id), sizeof(egg->id), free);
        list_rm_first_node(curteam->eggs_sorted, NULL);
    }
}

static void try_join_team_graphic(t_cli *c, char *strX, char *strY)
{
    t_msg     msg;

    msz(c, NULL);
    sgt(c, NULL);
    for (int64_t i = 0; i < c->servptr->map.height; i++)
    {
        for (int64_t j = 0; j < c->servptr->map.width; j++)
        {
            msg.params = new_list();
            strX = malloc(64);
            strY = malloc(64);
            snprintf(strX, 64, "%ld", j);
            snprintf(strY, 64, "%ld", i);
            list_append(&(msg.params), strX);
            list_append(&(msg.params), strY);
            bct(c, &msg);
            free(strX);
            free(strY);
            list_destruct(&(msg.params), NULL);
        }
    }
    tna(c, NULL);
    gui = c;
    ht_foreach(c->servptr->clients, pnw_init);
    list_for_each(c->servptr->teams, enw_init_list, NULL);
}
