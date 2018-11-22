import React, { Component } from 'react';
import { Tabs } from './config/router';
import constants from './global-constants';

export default class App extends Component {
	render() {
		return <Tabs screenProps={constants.github_profile[constants.github_profile.length-1]} />;
	}
}

