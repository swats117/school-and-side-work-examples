import React, { Component } from 'react';
import {
  Platform,
  StyleSheet,
  Text,
  FlatList,
  View,
  WebView,
  TouchableHighlight,
  Modal,
  Button,
  Dimensions,
} from 'react-native';
import axios from 'axios';
import {List, ListItem, SearchBar } from 'react-native-elements';
import constants from '../global-constants';
import styles from '../styles';

export default class Repositories extends Component {
  constructor(props){
    super(props);
    this.state = {refreshing:false, Repos:[], display_page:"", modalVisible:false};
    // Repo: {name, owner's github login, description}
  }
  componentDidMount(){
    console.log("Mounting repositories");
    console.log(constants.session_password);
    console.log("blah");
    user = constants.github_profile[constants.github_profile.length-1];
    axios(constants.github_api+user+'/repos')
    .then((response) => {
      console.log(response)
      let new_state = this.state;
      let repositories = response.data;
      repositories.forEach( ({name, owner, description, html_url}) =>{ 
        new_state.Repos.push({Name: name, Owner: owner.login, Description: description, URL: {uri: html_url} });
      });

      this.setState(new_state);
    })
  }
  render() {
    return(
      <View>
        <Modal
          animationType={'slide'}
          visible={this.state.modalVisible}
          onRequestClose={()=>{new_state = this.state; new_state.modalVisible=false; this.setState(new_state);}}
        > 
          <WebView source={this.state.display_page} />
           <Button
            onPress={() => {new_state = this.state; new_state.modalVisible=false; this.setState(new_state);}}
            title="Close"
          />
        </Modal>
        <List>
          <FlatList 
            contentContainerStyle={{paddingBottom: 0}}
            refreshing={this.state.refreshing}
            onRefresh={()=>{console.log("refreshing");}}
            data={this.state.Repos}
            renderItem={({ item })=>(
              <TouchableHighlight  onPress={()=>{  console.log("clicked!");
                                    new_state = this.state; 
                                    new_state.modalVisible = true;
                                    new_state.display_page = item.URL;
                                    this.setState(new_state); }}
                                    onLongPress={()=>{console.log("long pressed");}}
                                    >
              <View>
              <Text>{"Name: "+item.Name}</Text>
              <Text/>
              <Text>{"Owner:"+item.Owner}</Text>
              <Text/>
              <Text>{"Description: "+item.Description}</Text>
              </View>
              </TouchableHighlight>
            )}
            keyExtractor={ item => item.Name }
            ItemSeparatorComponent={()=>(<View style={styles.borderSeparator}/>)}
            ListHeaderComponent={()=>(<Button title="Last"
                onPress={()=>{console.log("working");}}
            />)}
            alwaysBounceVertical={true}
          />
        </List>
      </View>
    );
  }
}
