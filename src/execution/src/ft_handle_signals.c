/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:11:36 by maba              #+#    #+#             */
/*   Updated: 2024/10/14 15:12:51 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* ft_handle_signals() : Intercepte les signaux comme SIGINT et SIGQUIT, et définit les actions à prendre lorsque ces signaux sont reçus.
*
* Utilise : signal() ou sigaction()
*
*/