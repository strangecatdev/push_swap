/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:11:09 by myakoven          #+#    #+#             */
/*   Updated: 2024/03/23 19:19:19 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	char	**arg_arr;
	int		arg_count;

	stack_a = NULL;
	stack_b = NULL;
	arg_arr = NULL;
	if (argc < 2)
		return (ft_clean(arg_arr, &stack_a, &stack_b, 1));
	if (argc == 2)
		arg_arr = ft_split(argv[1], ' ');
	else
		arg_arr = makearray(argc, argv);
	if (!arg_arr)
		return (2);
	arg_count = ft_matrixlen(arg_arr);
	if (!ft_checkarray(arg_count, arg_arr))
		return (ft_clean(arg_arr, &stack_a, &stack_b, 2));
	stack_a = ft_init_list(arg_count, arg_arr);
	if (!stack_a || is_sorted(&stack_a))
		return (ft_clean(arg_arr, &stack_a, &stack_b, 3));
	ft_sort(&stack_a, &stack_b, arg_count);
	// TO DO
	// ft_index_list(stack_a);
	// ft_free_split_ps(arg_arr, (ft_matrixlen(arg_arr) - 1));
	free_array(arg_arr);
	return (0);
}

int	is_sorted(t_node **stack_a)
{
	t_node	*tmp;

	tmp = *stack_a;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->x < tmp->prev->x)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	**makearray(int argc, char **argv)
{
	char	**argv_replace;
	int		i;

	i = 0;
	argv_replace = malloc(sizeof(char *) * argc);
	if (!argv_replace)
		return (NULL);
	while (i < argc - 1)
	{
		argv_replace[i] = ft_strdup(argv[i + 1]);
		if (!argv_replace[i])
			return (free_array(argv_replace));
		i++;
	}
	argv_replace[i] = NULL;
	return (argv_replace);
}

int	ft_checkarray(int arg_count, char **arr)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	while (arr[i])
	{
		length = ft_strlen(arr[i] + 1);
		if (length > 11)
			return (error_fail());
		while (arr[j])
		{
			if (i != j && !ft_strncmp(arr[i], arr[j], length))
				return (error_fail());
			j++;
		}
		i++;
	}
	while (arr[i] && i < argc)
	{
		if (ft_atol(arr[i]) > INT_MAX || ft_atol(arr[i]) < INT_MIN)
			return (error_fail());
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				return (error_fail());
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_matrixlen(char **arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
// REWRITE OMG WHYYYYY
/******THIS NEEDS A COUNT LIMITER!!!**i dunno what this means*****/
t_node	*ft_init_list(int argc, char **argv)
{
	int		i;
	t_node	*temp;
	t_node	*head;
	t_node	*last;

	// t_node	**stack_a_init;
	// stack_a_init = NULL;
	if (argc == 2)
		argc = ft_matrixlen(argv);
	i = 0;
	head = ft_dlstnew(ft_atoi(argv[i++]));
	// stack_a_init = &head;
	temp = head;
	while (argv[i] && i < argc)
	{
		last = temp;
		temp = ft_dlstnew(ft_atol(argv[i++]));
		if (!temp)
		{
			(ft_dlstclear(&head));
			return (NULL);
		}
		last->next = temp;
		temp->prev = last;
	}
	temp->next = NULL;
	// WHY IS THIS HERE?
	// temp = ft_dlstnew(ft_atoi(argv[i++]));
	// if (!temp)
	// 	ft_dlstclear(stack_a_init);
	// ft_dlstadd_back(stack_a_init, temp);
	return (head);
}

// main
// FOR CHECKING
// swap(&stack_a);
// ft_printf("now printing %i \n", stack_a->x);
// ft_printf("initializes stack a %i \n", stack_a->next->x);
// ft_printf("prints last %i \n", stack_a->next->next->x);
// // ft_printf("should segv %i \n", stack_a->next->next->next->x);

// int	ft_arrsize(char **arr)
// {
// 	int	i;

// 	if (!arr)
// 		return (0);
// 	i = 0;
// 	while (arr[i])
// 		i++;
// 	return (i);
// }
