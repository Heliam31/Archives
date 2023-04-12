Require Import Arith .
Require Import Omega .
Require Export List .
Open Scope list_scope .
Import ListNotations.

Inductive isSorted : list nat -> Prop :=
|isSortedNil : isSorted nil
|isSortedCons : forall e h  :nat, forall q : list nat,
e <= h -> isSorted (h::q) -> isSorted(e::h::q)
|isSortedUn : forall e : nat, isSorted (e::nil).

Goal isSorted ([(S 0); (S(S 0)); (S(S(S 0)))]).
Proof.
apply isSortedCons.
auto.
apply isSortedCons.
auto.
apply isSortedUn.
Qed.


Inductive isPerm : list nat -> list nat -> Prop :=
|isPermReflex : forall l : list nat, isPerm l l
|isPermCons : forall l l': list nat, forall e:nat, isPerm l l' -> isPerm (e::l) (e::l')
|isPermConsApp : forall l l': list nat, forall e: nat, isPerm l l' -> isPerm (e::l) (l'++(e::nil))
|isPermSym : forall l l' : list nat, isPerm l l' -> isPerm l' l
|isPermTrans : forall l l' l'' : list nat, isPerm l l' -> isPerm l' l'' -> isPerm l l''
|isPermS : forall l l' l'' : list nat, forall e : nat, isPerm l (l' ++ l'') -> isPerm (e::l) (l' ++ (e::l'')).
 (*
Goal isPerm ([(S 0); (S(S 0)); (S(S(S 0)))]) ([(S(S(S 0)));(S(S 0));(S 0)])
Proof
subst *)

Check le_dec.
Print sumbool.

Definition le_10 ( n : nat ) : bool :=
match ( le_dec n 10 ) with
| left _ => true
| right _ => false
end .

Eval compute in le_10 15.

Fixpoint insert ( x : nat ) ( l : list nat ) { struct l } : list nat :=
match l with
|nil => [x]
|h::q => if (le_dec x h) then
          x::l
          else h::(insert x q)
end.

Eval compute in insert 3 [(S 0); (S(S 0)); (S(S(S 0))); (S(S(S(S 0)))); (S(S(S(S(S 0)))))].


Fixpoint isort (l : list nat) {struct l} : list nat :=
  match l with 
    | nil => nil
    | e::q => insert e (isort q)
  end.


Eval compute in (isort [5;4;2;3;1]).

Lemma head_is_perm : forall (x1 x2 : nat) (l : list nat), isPerm (x1 :: x2 :: l) (x2 :: x1 :: l).
Proof.
intros.
apply (isPermS (x2::l) [x2] l x1).
apply (isPermS l [] l x2).
simpl.
apply isPermReflex.
Qed.

Lemma insert_is_perm : forall (x : nat) (l : list nat), 
isPerm (x::l) (insert x l).
Proof.
intros.
induction l.
simpl.
apply isPermReflex.
simpl.
elim(le_dec x a).
intro.
apply isPermReflex.
intro.
apply isPermSym.
apply (isPermS (insert x l) [x] l a).
apply isPermSym.
apply IHl.
Qed.

