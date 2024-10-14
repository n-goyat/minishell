/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/10/14 15:07:44 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * ft_execute_pipeline() : Gère l'exécution des commandes connectées par des pipes (|), 
 * en redirigeant la sortie de la première commande vers l'entrée de la suivante, et ainsi de suite.
 * Entrée : Liste de commandes séparées par des pipes.
 * Utilise : pipe(), dup2(), fork(), execve().
*/

