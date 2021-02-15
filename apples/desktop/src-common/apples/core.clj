(ns apples.core
  (:require [play-clj.core :refer :all]
            [play-clj.g2d :refer :all]
            [play-clj.math :refer :all]))

(declare apples main-screen)
(def speed 40)

(defn- get-direction []  ;help method to return direction keys pressed by user
  (cond
   (key-pressed? :dpad-left) :left
   (key-pressed? :dpad-right) :right))

(defn- update-player-position [{:keys [player?] :as entity}]
  (if player?   ;;since we want to return the entire vector of maps but only want to move player - we need to use if player?
    (let [direction (get-direction)
          new-x (case direction
                  :right (+ (:x entity) speed)
                  :left (- (:x entity) speed))]
      (when (not= (:direction entity) direction)
        (texture! entity :flip true false))                  ;;flips cow to the right when going right and vice versa
      (assoc entity :x new-x :direction direction))
    entity))

(defn- update-hit-box [{:keys [player? apple?] :as entity}]
  (if (or player? apple?)   ;;move only player
    (assoc entity :hit-box (rectangle (:x entity) (:y entity) (:width entity) (:height entity)))
    entity))

(defn- remove-touched-apples [entities]
  (if-let [apples (filter #(contains? % :apple?) entities)]
    (let [player (some #(when (:player? %) %) entities)
          touched-apples (filter #(rectangle! (:hit-box player) :overlaps (:hit-box %)) apples)]
      (remove (set touched-apples) entities))
    entities))

(defn- move-player [entities]
  (->> entities
       (map (fn [entity]
              (->> entity
                   (update-player-position)
                   (update-hit-box))))
       (remove-touched-apples)))

(defn- spawn-apple []
  (let [x (+ 50 (rand-int 800))
        y (+ 50 (rand-int 30))]
    (assoc (texture "apple.png") :x x, :y y, :width 50, :height 65, :apple? true)))

(defscreen main-screen
  :on-show
  (fn [screen entities]        ;;screen is a set of useful settings & entities is my game state - a vector of clojure records
    (update! screen :renderer (stage))  
    (add-timer! screen :spawn-apple 10 1)
    (let [background (texture "apple_orchard.png") ;;vector of maps
          player (assoc (texture "cow.png") :x 50, :y 50, :width 200, :height 150, :player? true, :direction :right)]
      [background player])) ;;order of rendering - background first then player/cow
  
  :on-render
  (fn [screen entities]
    (clear!)
    (render! screen entities))
  
  :on-key-down  ;take in vector of maps and returns newly updated vector of maps
  (fn [screen entities]
    (cond
     (key-pressed? :r) (app! :post-runnable #(set-screen! apples main-screen))
     (get-direction) (move-player entities)
     :else entities))
  
  :on-timer
  (fn [screen entities]
    (case (:id screen)
      :spawn-apple (conj entities (spawn-apple)))))

(defgame apples
  :on-create
  (fn [this]
    (set-screen! this main-screen)))