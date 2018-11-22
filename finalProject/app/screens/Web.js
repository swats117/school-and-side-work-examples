import React, { Component } from 'react';
import {
  Text,
  View,
  WebView,
} from 'react-native';
import constants from '../global-constants';
import styles from '../styles';


export default class Web extends Component {

  render(){
    return (<View style={{flex:1}}><Text>hello</Text><WebView
        source={{uri: 'https://google.com'}}
        style={{marginTop: 20, flex:1,borderRadius: 4,
    borderWidth: 0.5,
    borderColor: '#d6d7da',}}
      /></View>);
  }
}
