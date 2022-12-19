#include<stdio.h>
#include<stdlib.h>
#include"shell_header.h"
t_cmd *heredoc()
{

}
t_cmd *lst_delete_node(t_cmd *cmd)
{
	 t_cmd *tmp;

    tmp = cmd;
    while(tmp)
    {
        if (!strcmp(tmp->command, " ")
            || !strcmp(tmp->command, "\"")
            || !strcmp(tmp->command, "\'"))
        {
          if (!tmp->prev && tmp->next)
          {
            cmd = tmp->next;
            tmp->next->prev = NULL;
          }
          else if (!tmp->next && tmp->prev)
              tmp->prev->next = NULL;
          else if (tmp->prev && tmp->next)
          {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
          }
          //free(tmp->command);
          //free(tmp);
          tmp = cmd;
        }
        else
          tmp = tmp->next;
    }    
    return (cmd);
}
int main()
{
    t_cmd *cmd;

    t_cmd cmd1;
    t_cmd cmd2;
    t_cmd cmd3;
    t_cmd cmd4;
  
    cmd1.command = " ";
    cmd1.prev = NULL;
    cmd2.command = " ";
    cmd2.prev = &cmd1;
    cmd1.next = &cmd2;
    cmd3.command = "a";
    cmd3.prev = &cmd2;
    cmd2.next = &cmd3;
    cmd3.next = &cmd4;
    cmd4.command = "ds";
    cmd4.next = NULL;
    cmd4.prev = &cmd3;
    t_cmd *tmp = lst_delete_node(&cmd1);
    while (tmp)
    {
        printf("command: %s\n",tmp->command);
        tmp = tmp->next;
    }
}