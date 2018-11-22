import React, { Component } from 'react';
import {
  View,
  Dimensions,
  TouchableOpacity,
  Text
} from 'react-native';
import { Camera }  from 'expo'
import constants from '../global-constants';
import styles from '../styles';


type Props = {};
export default class CameraUI extends Component<Props> {
  render(){
    return (<View style={{flex:1}}>
       <Camera style={{flex:1}}></Camera>
    </View>);
  }
}
