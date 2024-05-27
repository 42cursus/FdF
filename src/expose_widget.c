/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_widget.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:18:10 by abelov            #+#    #+#             */
/*   Updated: 2024/05/27 12:18:11 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*--------------------------------------------------------------------
force an immediate expose for the widget
----------------------------------------------------------------------*/

#include <X11/IntrinsicP.h>
#include <Xm/Xm.h>

/**
 * You may also have to set the XmNwidth and XmNheight resources
 * if you need consistent or predetermined sizes for the children.
 * In order to maintain the layout, you must add an event handler for resize
 * (ConfigureNotify) events
 */
void	expose_widget(Widget w)
{
	XExposeEvent xexpose;
	Dimension ww, hh;

	XtAppContext app;
	if (!XtIsRealized(w)) return;
	if (!XtIsManaged(w)) return;
	xexpose.window = XtWindow(w);
	if (xexpose.window == (Window) NULL) return;
	xexpose.type = Expose;
	xexpose.display = XtDisplay(w);
	xexpose.x = xexpose.y = 0;
	XtVaGetValues(w, XmNwidth, &ww, XmNheight, &hh, NULL);
	if (ww <= 0 || hh <= 0) return;
	xexpose.width = ww;
	xexpose.height = hh;
	XSendEvent(XtDisplay (w), XtWindow (w), True, ExposureMask, &xexpose);
	XFlush(XtDisplay(w));
}