import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios'

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    creds: {
      user: "",
      pass: ""
    },
    ad_stat: false,
    locked: false,
    sends: {
      method: 'ctrl',
      value: '',
      id: ''
    },
    modes: [
      {
        name: 'Rainbow',
        color: '(10,55,250)'
      },
      {
        name: 'Rnd-Rave',
        color: '(9,55,250)'
      }
    ],
    info: undefined,
    onOff: false,
    lk: {
      id: undefined,
      action: 'lock',
      value: undefined
    },
    rgb: '(0,0,0)',
    loading: false,
    tried_once: false,
    last_val: 0,
    res: null,
    snackShow: false,
    snackMessage: 'Oops?',
    snackColor: 'grey'
    // client: null
  },
  getters: {
    ad_stat: state => {
      var status = state.ad_stat
      return status
    }
  },
  mutations: {
    // Check login credentials
    cred_check: (state, payload) => {
      axios
        .put('https://ec4avk1xoh.execute-api.us-east-1.amazonaws.com/v1/', payload)
        .then(respons => {
          state.info = respons.data
          state.loading = false
          state.tried_once = true
          if (state.info.success) {
            state.ad_stat = true
            state.lk.id = state.info.id
          }
        })
    },
    // Check if main page is locked
    check_lock(){
      axios
        .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
        .then(respons => {
          var info = respons.data
          this.$store.state.locked = info.locked
        })
    },
    // Post everything to aws
    postRGB: (state) => {
      if (state.ad_stat == true) {
        state.sends.id = state.lk.id
      } else {
        state.sends.id = ""
        state.lk.id = ""
      }
      axios
      .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(state.sends))
      .then(respons => {
        state.info = respons.data
        state.loading = false
        state.snackShow = true;
        //Trigger snackbar
        if (state.info.Meddelande == 'Lyckades!'){
          state.snackMessage = 'Success!'
          state.snackColor = 'green'
        }else{
          state.snackMessage = 'Failed!'
          state.snackColor = 'red'
        }
        // If page is locked
        if (state.info.Meddelande == 'låst!'){
          axios
            .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
            .then(respons => {
              var info = respons.data
              state.locked = info.locked
          })
        }
      })
    },
    log_out: (state) => {
      state.ad_stat = false
      state.creds = {
        user: undefined,
        pass: undefined
      }
      state.tried_once = false
    },
    //Lock the main page
    lock: (state) => {
      if (state.locked) {
        state.lk.value = false
        axios
          .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1', JSON.stringify(state.lk))
          .then(respons => {
            state.info = respons.data
          })
        state.locked = false
      } else {
        state.lk.value = true
        axios
          .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1', JSON.stringify(state.lk))
          .then(respons => {
            state.info = respons.data
          })
        state.locked = true
      }
    },
  },
  //Actions to async
  //Actions that trigger mutations to allow for better trace back on error
  actions: {
    cred_check: (context, payload) => {
      context.commit('cred_check', payload)
    },
    log_out: (context) => {
      context.commit('log_out')
    },
    postRGB: (context) => {
      context.commit('postRGB')
    },
    lock: (context) => {
      context.commit('lock')
    }
  }
})

export default store