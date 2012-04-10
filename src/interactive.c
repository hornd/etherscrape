#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interactive.h"
#include "printer.h"
#include "util.h"

#define  BUF_MAX  128

typedef enum
{
    GRID,
    FOCUSED
} shell_state;


typedef shell_state (*disp_function)(void);

struct cmds
{
    char *cmd;
    char *verbose_cmd;    
    char *help;
    disp_function handle;
};

char *prompt = "eth> ";

static shell_state grid_next_handle();
static shell_state grid_prev_handle();
static shell_state grid_disp_handle();
static shell_state grid_help_handle();
static shell_state exit_handle();

static shell_state handle_grid_input(char *);
static shell_state handle_focused_input(char *);
static void shell();

#define NUM_GRID_COMMANDS 5
static struct cmds 
grid_commands[NUM_GRID_COMMANDS] = { { "n", "next", "Next Page", grid_next_handle },
                                     { "p", "prev", "Previous Page", grid_prev_handle },
                                     { "d", "display", "Redisplay Page", grid_disp_handle },
                                     { "h", "help", "Help", grid_help_handle },
                                     { "q", "quit", "Quit ", exit_handle } };

#define NUM_FOCUS_COMMANDS 3
static struct cmds
focus_commands[NUM_FOCUS_COMMANDS] = { {"r", "raw", "Raw hex output", NULL },
                                       {"q", "quit", "Quit", exit_handle },
                                       {"b", "back", "Back to Grid", NULL } };

extern void
go_interactive()
{
    display_grid();
    shell();
}

static void
shell()
{
    char buf[BUF_MAX];
    shell_state state = GRID;
    
    printf("\n%s", prompt);
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

        printf("\n%s", prompt);
    }
}


static shell_state grid_next_handle() 
{ 
    if (!grid_next())
    {
        printf("No more packets captured\n");
    }
    return GRID;
}

static shell_state grid_prev_handle() 
{ 
    grid_prev();
    return GRID;
}

static shell_state grid_disp_handle() 
{
    display_grid();
    return GRID;
}

static shell_state grid_help_handle() 
{
    uint8_t i;
    for(i=0; i<NUM_GRID_COMMANDS; i++)
    {
        printf("%s: %s\n", grid_commands[i].cmd, grid_commands[i].help);
    }    
    return GRID;
}

static shell_state exit_handle() { exit(0); }

static shell_state
handle_grid_input(char *str)
{
    uint8_t i;

    if (is_numeric(str))
    {
        return FOCUSED;
    }

    for(i=0; i<NUM_GRID_COMMANDS; i++)
    {
        if (!strcmp(str, grid_commands[i].cmd) || !strcmp(str, grid_commands[i].verbose_cmd))
        {
            return grid_commands[i].handle();
        }
    }

    printf("Invalid command. Type 'h' for options\n");
    return GRID;
}

static shell_state 
handle_focused_input(char *str)
{
    uint8_t i;
    uint32_t val = atoi(str);

    for(i=0; i<NUM_FOCUS_COMMANDS; i++)
    {
        if (!strcmp(str, focus_commands[i].cmd) || !strcmp(str, focus_commands[i].verbose_cmd))
        {
            return focus_commands[i].handle();
        }
    }

    printf("Invalid command. Type 'h' for options\n");
    return GRID;

    return FOCUSED;
}



