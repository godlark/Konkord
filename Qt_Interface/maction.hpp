/*				Konkord 
 *		    Version 0.0.2009.04.19
 *	This program was created for learning words
 *		    from different languages.
 *    Copyright(C) 2009 Sławomir Domagała	
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *																			
 * This program is distributed in the hope that it will be useful,				
 * but WITHOUT ANY WARRANTY; without even the implied warranty of				
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				
 * GNU General Public License for more details.								
 *																			
 * You should have received a copy of the GNU General Public License			
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *																				
 * E-mail: E-mail: g_o_d_l_a_r_k / monkey / g_m_a_i_l / dot / c_o_m									
 */
#ifndef MACTION_HPP
#define MACTION_HPP

#include <QAction>

class MAction: public QAction {
	Q_OBJECT;
	
public:
	MAction ( QObject * parent);
	MAction ( const QString & text, QObject * parent);
	MAction ( const QIcon & icon, const QString & text, QObject * parent);
	~MAction ();
	
signals:
	MAction* _changed(MAction*);
	MAction* _hovered(MAction*);
	MAction* _toggled(MAction*, bool);
	MAction* _triggered(MAction*);
	MAction* _triggered(MAction*, bool);
	
public slots:
	void slotChanged();
	void slotHovered();
	void slotToggled(bool);
	void slotTriggered();
	void slotTriggered(bool);
};

#endif
