import React, { Component } from 'react';
import {
  Text,
  FlatList,
  View,
  KeyboardAvoidingView,
  Dimensions,
  TextInput,
} from 'react-native';
import {List, ListItem} from 'react-native-elements';
import constants from '../global-constants';
import styles from '../styles';



type Props = {};
export default class Chat extends Component<Props> {

  constructor(props){
    super(props);
    this.state = {
      messages:["message 1","message 2"],
      text_input_value:""
    }
  }

  render(){
    return (<KeyboardAvoidingView
          style={{flex:1}}
          behavior="padding"
        >
      <Text></Text>
      <Text></Text>
        <View 
          style={{flex:1}}
          >
        <FlatList
        inverted
        style={{height: Dimensions.get("window").height*(2/3)}}
        data={this.state.messages}
        renderItem={({ item })=>(
              <View>
                <Text></Text>
                <Text>{item}</Text>
                <Text></Text>
              </View>
            )}
        keyExtractor={ item => item.Login }
        ItemSeparatorComponent={()=>(<View style={styles.borderSeparator}/>)}
        alwaysBounceVertical={true}
        />
        </View>

      <TextInput

      autoFocus = {false}
                  placeholder="message"
                  keyboardType="default"
                  returnKeyType="done"
                  style={{height: 40, borderColor: 'gray', borderWidth: 1, textAlign:"center" }}
                  onSubmitEditing={
                    (event)=>{
                      new_message = event.nativeEvent.text;
                      new_state = this.state;
                      new_state.messages.unshift(new_message);
                      new_state.text_input_value = "";
                      this.setState(new_state);
                    }
                  }
                  onChangeText={(text) => {
                      this.state.text_input_value=text
                      this.setState(this.state)}}
                  value={this.state.text_input_value}
      >
      </TextInput>
    </KeyboardAvoidingView>);
  }
}


