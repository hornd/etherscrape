#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interactive.h"
#include "printer.h"
#include "grid.h"
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

static shell_state focused_raw_handle();
static shell_state focused_help_handle();

static shell_state handle_grid_input_numeric(const char *);
static shell_state handle_grid_input_non_numeric(const char *);
static shell_state handle_grid_input(const char *);
static shell_state handle_focused_input(char *);
static void shell();

#define NUM_GRID_COMMANDS 5
static const struct cmds 
grid_commands[NUM_GRID_COMMANDS] = { { "n", "next", "Next Page", grid_next_handle },
                                     { "p", "prev", "Previous Page", grid_prev_handle },
                                     { "d", "display", "Redisplay Page", grid_disp_handle },
                                     { "h", "help", "Help", grid_help_handle },
                                     { "q", "quit", "Quit ", exit_handle } };

#define NUM_FOCUS_COMMANDS 4
static const struct cmds
focus_commands[NUM_FOCUS_COMMANDS] = { {"r", "raw", "Raw hex output", focused_raw_handle },
                                       {"q", "quit", "Quit", exit_handle },
                                       {"h", "help", "Help", focused_help_handle },
                                       {"b", "back", "Back to Grid", grid_disp_handle } };

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

static shell_state 
grid_next_handle() 
{ 
    if (!grid_next())
    {
        printf("No more packets captured\n");
    }
    return GRID;
}

static shell_state 
grid_prev_handle() 
{ 
    grid_prev();
    return GRID;
}

static shell_state 
grid_disp_handle() 
{
    display_grid();
    return GRID;
}


static void help_handle(const struct cmds *all, const uint8_t len) 
{
    uint8_t i;
    for(i=0; i<len; i++) 
    {
        printf("%s: %s\n", all[i].cmd, all[i].help);
    }
}


static shell_state 
grid_help_handle() 
{
    help_handle(grid_commands, NUM_GRID_COMMANDS);
    return GRID;
}

static shell_state 
exit_handle() 
{ 
    exit(0); 
}

static shell_state
focused_help_handle()
{
    help_handle(focus_commands, NUM_FOCUS_COMMANDS);
    return FOCUSED;
}

static shell_state 
focused_raw_handle() 
{
    if(!focused_raw_print())
    {
        printf("Unable to dump raw packet...\n");
    }

    return FOCUSED;
}

static shell_state
handle_grid_input_numeric(const char *str)
{
    if (grid_focus(atoi(str)))
    {
        return FOCUSED;
    }
    else
    {
        printf("Invalid packet ID. Type 'h' for options\n");
        return GRID;
    }
}

static shell_state
handle_grid_input_non_numeric(const char *str)
{
    uint8_t i;
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
handle_grid_input(const char *str)
{
    if (is_numeric(str))
    {
        return handle_grid_input_numeric(str);
    }
    
    return handle_grid_input_non_numeric(str);
}

static shell_state 
handle_focused_input(char *str)
{
    uint8_t i;
/*    uint32_t val = atoi(str); */

    for(i=0; i<NUM_FOCUS_COMMANDS; i++)
    {
        if (!strcmp(str, focus_commands[i].cmd) || !strcmp(str, focus_commands[i].verbose_cmd))
        {
            return focus_commands[i].handle();
        }
    }

    printf("Invalid command. Type 'h' for options\n");
    return FOCUSED;
}



