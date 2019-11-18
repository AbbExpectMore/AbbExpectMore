export default [{
    path: '/',
    name: 'Home',
    view: 'Home',
    //   component: Home
  },
  {
    path: '/About',
    name: 'About',
    view: 'About',
    //   component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  },
  {
    path: '/Help',
    name: 'Help',
    view: 'Help',
    //   component: () => import(/* webpackChunkName: "about" */ '../views/GetAnswer.vue')
  }
];