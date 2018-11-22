import React from 'react';
import { TabNavigator } from 'react-navigation';
import Icon from 'react-native-vector-icons/FontAwesome';
import Icon2 from 'react-native-vector-icons/MaterialCommunityIcons';

import styles from '../styles'
import Camera from '../screens/Camera';
import Video from '../screens/Video';
import Web from '../screens/Web';
import Chat from '../screens/Chat';
import constants from '../global-constants';

export const Tabs = TabNavigator(
{
	Web: {
		screen: Web,
		navigationOptions: () => ({
			tabBarIcon: () => <Icon2 name="web" size={30} />,
			tabBarLabel: 'Web Search',
		}),
	},
	Video: {
		screen: Video,
		navigationOptions: () => ({
			tabBarIcon: () => <Icon name="play" size={30} />,
			tabBarLabel: 'Video',
		}),
	},
	Chat: {
		screen: Chat,
		navigationOptions: () => ({
			tabBarIcon: () => <Icon name="envelope-o" size={30} />,
			tabBarLabel: 'Chat',
		}),
	},
	Camera: {
		screen: Camera,
		navigationOptions: () => ({
			tabBarIcon: () => <Icon name="camera" size={30} />,
			tabBarLabel: 'Camera',
		}),
	},
},
{swipeEnabled:true},
{animationEnabled:true},
{
	tabBarPosition: 'bottom',
    tabBarOptions: {
        showIcon: true,
        style: {
        	height: constants.tab_bar_height,
        },
        labelStyle: {
			fontSize: 12,
		}
	}
});





























