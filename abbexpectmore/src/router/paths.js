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
    path: '/Admin',
    name: 'Admin',
    view: 'Admin',
    //   component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  },
  {
    path: '/colors',
    name: 'Colors',
    view: 'Colors',
    //   component: () => import(/* webpackChunkName: "about" */ '../views/GetAnswer.vue')
  },
  {
    path: '/settings',
    name: 'Settings',
    view: 'Settings'
  }
];