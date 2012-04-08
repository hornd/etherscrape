#include <stdio.h>
#include <string.h>
#include "interactive.h"
#include "printer.h"
#include "util.h"

#define  BUF_MAX  128

char *grid_commands[] = 
{
    "n", /* next page of grid */
    "p", /* prev page of grid */
};

char *focused_commands[] = 
{
    "r", /* raw packet output */
    "b", /* back to grid view */
    "q", /* quit */
};

typedef enum
{
    GRID,
    FOCUSED
} shell_state;

static shell_state handle_grid_input(char *);
static shell_state handle_focused_input(char *);

static void
shell()
{
    char buf[BUF_MAX];
    shell_state state = GRID;
    
    printf("\n\n> ");
    while(fgets(buf, BUF_MAX, stdin))
    {
        buf[strlen(buf)-1] = '\0';
        if (state == GRID) 
        {
            state = handle_grid_input(buf);
        }
        else
        {
            state = handle_focused_input(buf);
        }

        printf("\n\n> ");
    }
}

static shell_state 
handle_grid_input(char *str)
{
    if (is_numeric(str)) 
    {
        
    }
    else if (!strcmp(str, "q") || !strcmp(str, "quit"))
    {
        exit(0);
    }

    return GRID;
}

static shell_state 
handle_focused_input(char *str)
{
    return FOCUSED;
}

extern void
go_interactive()
{
    display_grid();
    shell();
}


