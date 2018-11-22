import React, { Component } from 'react';
import {
  Text,
  View,
  Dimensions,
  TouchableHighlight,
} from 'react-native';
import { Video } from 'expo';
import Icon from 'react-native-vector-icons/FontAwesome';
import constants from '../global-constants';
import styles from '../styles';


type Props = {};
export default class VideoPlayer extends Component<Props> {

  _mountVideo = component => {
    this._video = component;
  };

  constructor(props){
    super(props);
    this.state =  {
                    mute: false,
                    shouldPlay: false,
                  }
  }

 render(){
    return (
      <View
        style={styles.container}>
        <Text></Text>
        <TouchableHighlight 
          onPress={()=> {
                newState = this.state;
                console.log(newState);
                newState.shouldPlay = !newState.shouldPlay;
                this.setState(newState);
              }
          }
          activeOpacity={0}
          style={styles.container}
        >
          <Video
            ref={this._mountVideo}
            source={require('../assets/AlPachino.mp4')}
            shouldPlay={this.state.shouldPlay}
            onPlaybackStatusUpdate={
              (playbackObject)=>{
                console.log(playbackObject)
                if(playbackObject.didJustFinish){
                  newState = this.state;
                  newState.shouldPlay = false;
                  this._video.setPositionAsync(0);
                  this.setState(newState);
                }
              }
            }
            isMuted={this.state.mute}
            style={{flex:1}}
            resizeMode="contain"
          />
        </TouchableHighlight>
        <View
          style={styles.container}>
          <View style={styles.controlBar}>
            <TouchableHighlight 
              style={{flex:1,alignItems:'center',flexDirection:'column'}}
              onPress={()=> {
                              this._video.
                              pauseAsync().
                              then((playerStatus) => {
                                newPosition = playerStatus.positionMillis;
                                newPosition -= 1000;
                                newPosition = newPosition > 0 ? newPosition : 0 ;
                                this._video.playFromPositionAsync(newPosition)
                              });
                            }
                        }
              >
              <View 
                style={{flex:1,alignItems:'center',flexDirection:'row'}}>
              <Icon 
                
                name={"fast-backward"}
                size={60} 
                
              />
              </View>
            </TouchableHighlight>
            <TouchableHighlight
              style={{flex:1,alignItems:'center',flexDirection:'column'}}
              onPress={()=> {
                              this._video.
                              pauseAsync().
                              then((playerStatus) => {
                                newPosition = playerStatus.positionMillis;
                                newPosition += 1000;
                                newPosition = newPosition > 0 ? newPosition : 0 ;
                                this._video.playFromPositionAsync(newPosition)
                              }); 
                            }
                          }
              >

              <View 
                style={{flex:1,alignItems:'center',flexDirection:'row'}}>
                <Icon 
                  name={"fast-forward"}
                  size={60} 
                />
              </View>
            </TouchableHighlight>
          </View> 
        </View>
        
      </View>
    );
  }
}



